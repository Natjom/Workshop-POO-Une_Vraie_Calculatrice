#ifndef STATES_HPP
#define STATES_HPP

#include "AbstractState.hpp"
#include <iostream>

class State1 : public AbstractState {
public:
    void action() const override {
        std::cout << "Action de l'etat E1" << std::endl;
    }
};

class State2 : public AbstractState {
public:
    void action() const override {
        std::cout << "Action de l'etat E2" << std::endl;
    }
};

class State3 : public AbstractState {
public:
    void action() const override {
        std::cout << "Action de l'etat E3" << std::endl;
    }
};

class State4 : public AbstractState {
public:
    void action() const override {
        std::cout << "Action de l'etat E4" << std::endl;
    }
};

#endif // STATES_HPP