#include "UniqueList.hpp"

using namespace std;

#include <iostream>
#include "UniqueList.hpp"

int main() {
    UniqueList liste;

    for (int i = 0; i < 10; i++) {
        liste.add(rand() % 100 + 1);
    }
    liste.print();

    for (int i = 0; i < 5; i++) {
        int value = liste.get(i);
        if (liste.add(value)) {
            std::cout << value << " has been added to the list." << std::endl;
        } else {
            std::cout << value << " is already in the list." << std::endl;
        }
    }

    for (int i = 5; i < 10; i++) {
        int value = liste.get(i);
        if (liste.remove(value)) {
            std::cout << value << " has been removed." << std::endl;
        } else {
            std::cout << value << " doesn't exist." << std::endl;
        }
    }

    liste.print();

    return 0;
}

