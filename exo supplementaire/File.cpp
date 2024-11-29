#include "File.hpp"
#include <iostream>

File::File() : front(nullptr), rear(nullptr) {}

File::~File() {
    while (front != nullptr) {
        removeClient();
    }
}

void File::addClient(const Client& c) {
    Node* newNode = new Node(c);
    
    if (rear == nullptr) {  
        front = rear = newNode;
    } else {  
        rear->next = newNode;
        rear = newNode;
    }
}

void File::removeClient() {
    if (front == nullptr) { 
        std::cout << "La file est vide, rien à supprimer." << std::endl;
        return;
    }
    Node* temp = front;     
    front = front->next;  
    if (front == nullptr) {  
        rear = nullptr;
    }
    std::cout << "Client retire: " << temp->client.getName() << std::endl;
    delete temp; 
}

void File::printClients() const {
    Node* current = front;
    while (current != nullptr) {
        std::cout << "Client ID: " << current->client.getId() 
                  << ", Name: " << current->client.getName() << std::endl;
        current = current->next;
    }
}
