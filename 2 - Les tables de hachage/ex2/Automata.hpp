#ifndef AUTOMATA_HPP
#define AUTOMATA_HPP

#include <iostream>
#include <map>
#include <memory>
#include "AbstractState.hpp" 

enum class stateId {
    E1, E2, E3, E4, NULL_STATE
};

class Automata {
private:
    std::map<stateId, std::shared_ptr<AbstractState>> states;
    std::map<stateId, stateId> delta;
    stateId currentState;

public:
    Automata();

    void initAutomata();
    void transition();
    void action();
    void run();
};

#endif // AUTOMATA_HPP
