//
//  StateTransition.cpp
//  TuringMachineInterpreter
//
//  Created by Dana Zagar on 2017-03-14.
//  Copyright © 2017 Dana Zagar. All rights reserved.
//

#include "StateTransition.hpp"

//Default constructor
StateTransition::StateTransition(){}

StateTransition::StateTransition(std::vector<std::string> s){
    StateTransition::currentState = stoi(s[1]);
    StateTransition::input = s[2][0];
    StateTransition::next = stoi(s[3]);
    StateTransition::output = s[4][0];
    StateTransition::dir = s[5][0];
}

bool StateTransition::Move(std::string &tp, std::string &cs, size_t &pos){
    if (std::stoi(cs) == StateTransition::currentState && tp[pos] == StateTransition::input){
        cs = std::to_string(StateTransition::next);
        tp[pos] = StateTransition::output;
        if (StateTransition::dir == 'R'){
            pos++;
        } else if (StateTransition::dir == 'L'){
            pos--;
        } else if (StateTransition::dir == 'H'){
            pos = tp.length();
        }
        return true;
    }
    return false;
}

//Destructor
StateTransition::~StateTransition(){}
