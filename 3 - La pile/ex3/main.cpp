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

void testParser()
{
    Parser parser;

    assert(parser.parse("((9+5)+((3+1)+(2+4)))") == 30);
    assert(parser.parse("(1+1)") == 2);
    assert(parser.parse("((1+1)+1)") == 3);

    std::cout << "All tests passed!" << std::endl;
}

int main()
{
    Parser parser;

    std::string expression = "((9+5)*((3+2)+(2+4)))";
    int result = parser.parse(expression);

    std::cout << "Result: " << result << std::endl; 
    return 0;
}
