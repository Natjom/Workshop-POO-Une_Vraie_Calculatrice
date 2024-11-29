#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cassert>
#include <cctype>

enum class TokenType
{
    Number,
    Operator,
    Parenthesis,
    Unknown
};

class Token
{
public:
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string &v) : type(t), value(v) {}

    bool isOperator() const
    {
        return type == TokenType::Operator;
    }

    bool isNumber() const
    {
        return type == TokenType::Number;
    }
};

class Lexer
{
public:
    std::vector<Token> lex(const std::string &input)
    {
        std::vector<Token> tokens;
        size_t i = 0;

        while (i < input.size())
        {
            char c = input[i];

            if (isspace(c))
            {
                i++;
                continue;
            }

            if (isdigit(c))
            {
                std::string num = "";
                while (i < input.size() && isdigit(input[i]))
                {
                    num += input[i];
                    i++;
                }
                tokens.push_back(Token(TokenType::Number, num));
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                tokens.push_back(Token(TokenType::Operator, std::string(1, c)));
                i++;
            }
            else if (c == '(' || c == ')')
            {
                tokens.push_back(Token(TokenType::Parenthesis, std::string(1, c)));
                i++;
            }
            else
            {
                tokens.push_back(Token(TokenType::Unknown, std::string(1, c)));
                i++;
            }
        }

        return tokens;
    }
};

class Expression
{
public:
    virtual int evaluate() = 0;
    virtual ~Expression() {}
};

class Number : public Expression
{
    int value;

public:
    Number(int v) : value(v) {}
    int evaluate() override
    {
        return value;
    }
};

class Operator
{
public:
    virtual int apply(int left, int right) = 0;
    virtual ~Operator() {}
};

class BinaryOp : public Operator
{
    char op;

public:
    BinaryOp(char o) : op(o) {}

    int apply(int left, int right) override
    {
        if (op == '+')
            return left + right;
        if (op == '-')
            return left - right;
        if (op == '*')
            return left * right;
        if (op == '/')
            return left / right;
        return 0;
    }
};

class Parser
{
    Lexer lexer;

public:
    int parse(const std::string &input)
    {
        std::vector<Token> tokens = lexer.lex(input);
        std::stack<Expression *> operandStack;
        std::stack<Operator *> operatorStack;

        for (auto &token : tokens)
        {
            if (token.isNumber())
            {
                operandStack.push(new Number(std::stoi(token.value)));
            }
            else if (token.value == "(")
            {
                operatorStack.push(nullptr); 
            }
            else if (token.value == ")")
            {
                while (!operatorStack.empty() && operatorStack.top() != nullptr)
                {
                    Operator *op = operatorStack.top();
                    operatorStack.pop();
                    Expression *right = operandStack.top();
                    operandStack.pop();
                    Expression *left = operandStack.top();
                    operandStack.pop();
                    operandStack.push(new Number(op->apply(left->evaluate(), right->evaluate())));
                    delete op;
                }
                operatorStack.pop();
            }
            else if (token.isOperator())
            {
                char op = token.value[0];
                operatorStack.push(new BinaryOp(op));
            }
        }
        while (!operatorStack.empty())
        {
            Operator *op = operatorStack.top();
            operatorStack.pop();
            Expression *right = operandStack.top();
            operandStack.pop();
            Expression *left = operandStack.top();
            operandStack.pop();
            operandStack.push(new Number(op->apply(left->evaluate(), right->evaluate())));
            delete op;
        }

        int result = operandStack.top()->evaluate();
        delete operandStack.top();
        return result;
    }
};


void test(Parser parser, std::string exp) {
    int result = parser.parse(exp);
    std::cout << "Expression: " << exp << " -> Result: " << result << std::endl;
}

int main()
{
    Parser parser;

    // Tests simples
    test(parser, "(1+1)"); // 2
    test(parser, "(2+2)"); // 4
    test(parser, "(5-3)"); // 2
    test(parser, "(3*3)"); // 9
    test(parser, "(6/2)"); // 3

    // Tests avec plusieurs opérateurs
    test(parser, "((1+2)*(3+4))"); // (3 * 7) = 21
    test(parser, "((5+3)/(2+2))"); // (8 / 4) = 2

    // Tests avec des parenthèses imbriquées
    test(parser, "(((1+2)+3)+4)"); // ((3+3)+4) = 10
    test(parser, "(((((1+1)+1)+1)+1)+1)"); // 6

    // Tests avec des opérateurs de différents types
    test(parser, "(2+2)*(3-1)"); // 4 * 2 = 8
    test(parser, "(6-2)*(4+1)"); // 4 * 5 = 20
    test(parser, "((5*5)+(3+2))"); // 25 + 5 = 30
    test(parser, "(6/(3-1))*(2+2)"); // 3 * 4 = 12

    // Tests avec des calculs plus complexes
    test(parser, "((9+5)*((3+2)+(2+4)))"); // (14 * (5 + 6)) = 154
    test(parser, "(((1+1)*(2+3))/(3))"); // ((2 * 5) / 3) = 3
    test(parser, "(((3+2)*(2+4))/(4))"); // ((5 * 6) / 4) = 7
    test(parser, "(((5+5)*(4+1))/(5))"); // ((10 * 5) / 5) = 10

    // Cas limite
    test(parser, "(((9+9)+(9+9))*(9/9))"); // ((18 + 18) * 1) = 36
    test(parser, "(((((1+1)+1)+1)+1)+1)"); // 6
    test(parser, "(1+1)+(1+1)+(1+1)"); // 2 + 2 + 2 = 6

    // Tests avec division
    test(parser, "(6/3)+(9/3)"); // 2 + 3 = 5
    test(parser, "(9/(3+3))"); // 9 / 6 = 1 (division flottante ou erreur si entiers)
    
    // Tests avec expressions complexes et profondeur de parenthèses
    test(parser, "((((((2+2)*2)-3)/2)+4)*2)"); // Complexe, évaluer étape par étape
    test(parser, "((3+5)*(6-4))"); // 8 * 2 = 16
    test(parser, "(((9-3)*(4+1))/5)"); // (6 * 5) / 5 = 6

    // Cas avec des expressions entièrement imbriquées
    test(parser, "((((((((1+2)+3)+4)+5)+6)+7)+8)+9)+10)"); // 55 
    test(parser, "(((((((2+3)+4)+5)+6)+7)+8)+9))"); // 44

    std::cout << "All tests completed!" << std::endl;

    return 0;
}

