#include <iostream>
#include <vector>

void tri_insertion(std::vector<int>& vect, int new_element) {
    vect.push_back(new_element);
    int i = vect.size() - 1;  
    int v = vect[i];         
    while (i > 0 && vect[i - 1] > v) {
        vect[i] = vect[i - 1];
        --i;
    }
    vect[i] = v;
}

int main() {
    std::vector<int> sorted_vect = {1, 3, 5, 7, 9};
    std::vector<int> new_elements = {4, 1 , 2, 10, 6};
    for (int elem : new_elements) {
        tri_insertion(sorted_vect, elem);
    }
    std::cout << "Final sorted Vecteur : { ";
    for (int val : sorted_vect) {
        std::cout << val << " ";
    }
    std::cout << "}" << std::endl;

    return 0;
}
