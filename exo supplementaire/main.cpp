#include "File.hpp"
#include "Client.hpp"
#include <iostream>

int main() {
    File file;
    file.addClient(Client("Alice", 1));
    file.addClient(Client("Bob", 2));
    file.addClient(Client("Charlie", 3));
    std::cout << "Liste des clients apres ajout : " << std::endl;
    file.printClients();
    file.removeClient();  
    file.removeClient();  
    std::cout << "Liste des clients apres suppression : " << std::endl;
    file.printClients();
    file.removeClient();
    file.removeClient();
    return 0;
}
