#include "Client.hpp"

Client::Client(std::string name, int id) : name(name), id(id) {}

std::string Client::getName() const {
    return name;
}

int Client::getId() const {
    return id;
}
