#include "Automata.hpp"
#include "States.hpp"  

Automata::Automata() {
    currentState = stateId::E1;  
}

void Automata::initAutomata() {
    states[stateId::E1] = std::make_shared<State1>();
    states[stateId::E2] = std::make_shared<State2>();
    states[stateId::E3] = std::make_shared<State3>();
    states[stateId::E4] = std::make_shared<State4>();

    delta[stateId::E1] = stateId::E2;
    delta[stateId::E2] = stateId::E3;
    delta[stateId::E3] = stateId::E4;
    delta[stateId::E4] = stateId::NULL_STATE;
}

void Automata::transition() {
    if (delta.find(currentState) != delta.end()) {
        currentState = delta[currentState];
    }
}

void Automata::action() {
    if (states.find(currentState) != states.end()) {
        states[currentState]->action();
    }
}

void Automata::run() {
    while (currentState != stateId::NULL_STATE) {
        action();
        transition();
    }
    std::cout << "Automate termine." << std::endl;
}
