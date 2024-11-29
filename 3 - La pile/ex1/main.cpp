#include <iostream>
#include <stack>

class ChangeBase {
public:
    std::stack<int> toBase(int n, int b) {
        std::stack<int> resultStack;
        if (n <= 0 || b <= 0 || b > 10) {
            std::cerr << "Erreur: n doit être > 0 et b doit être entre 1 et 10." << std::endl;
            return resultStack;
        }
        while (n != 0) {
            resultStack.push(n % b);
            n = n / b;
        }
        return resultStack;
    }

    void print(std::stack<int> stack) {
        while (!stack.empty()) {
            std::cout << stack.top();
            stack.pop();
        }
        std::cout << std::endl;
    }
};

int main() {
    ChangeBase cb;
    int n, b;
    std::cout << "Entrez un entier n : ";
    std::cin >> n;
    std::cout << "Entrez une base b (1 <= b <= 10) : ";
    std::cin >> b;
    std::stack<int> result = cb.toBase(n, b);
    std::cout << "Le nombre " << n << " en base " << b << " est : ";
    cb.print(result);
    return 0;
}
