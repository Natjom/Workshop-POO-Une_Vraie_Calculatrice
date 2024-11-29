#include <iostream>
#include <stack>
#include <vector>

class SortedList {
private:
    std::stack<int> sortedStack;

public:
    SortedList(const std::vector<int>& unsortedList) {
        for (int num : unsortedList) {
            sortedStack.push(num);
        }
    }
    void sort() {
        std::stack<int> origStack;
        std::stack<int> ordStack;
        while (!sortedStack.empty()) {
            origStack.push(sortedStack.top());
            sortedStack.pop();
        }
        while (!origStack.empty()) {
            int current = origStack.top();
            origStack.pop();
            while (!ordStack.empty() && ordStack.top() > current) {
                origStack.push(ordStack.top());
                ordStack.pop();
            }
            ordStack.push(current);
        }
        sortedStack = ordStack;
    }
    void print() {
        std::stack<int> tempStack = sortedStack;
        while (!tempStack.empty()) {
            std::cout << tempStack.top() << " ";
            tempStack.pop();
        }
        std::cout << std::endl;
    }
};

int main() {
    std::vector<int> unsortedList = {1, 11, 3, 7, 5};
    SortedList list(unsortedList);
    list.sort();
    std::cout << "Liste triee: ";
    list.print();

    return 0;
}
