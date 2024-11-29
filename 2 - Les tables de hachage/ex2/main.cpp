#include "AbstractState.hpp"
#include "Automata.hpp"
#include "States.hpp"

#include <iostream>
#include <vector>
#include <map>


int main() {
    Automata automata;
    automata.initAutomata();
    automata.run(); 
    return 0;
}