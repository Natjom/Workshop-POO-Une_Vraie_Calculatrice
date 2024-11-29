#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
public:
    std::string name;
    int id;
    Client(std::string name, int id);
    std::string getName() const;
    int getId() const;
};

#endif // CLIENT_HPP
