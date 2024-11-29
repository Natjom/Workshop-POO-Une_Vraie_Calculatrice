#ifndef FILE_HPP
#define FILE_HPP

#include "Client.hpp"

class File {
private:
    struct Node {
        Client client;  
        Node* next;   

        Node(Client c) : client(c), next(nullptr) {} 
    };

    Node* front; 
    Node* rear;  

public:
    File(); 
    ~File(); 

    void addClient(const Client& c);  
    void removeClient();              
    void printClients() const;       
};

#endif // FILE_HPP
