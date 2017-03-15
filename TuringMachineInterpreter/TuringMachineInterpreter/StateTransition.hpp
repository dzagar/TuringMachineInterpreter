//
//  StateTransition.hpp
//  TuringMachineInterpreter
//
//  Created by Dana Zagar on 2017-03-14.
//  Copyright © 2017 Dana Zagar. All rights reserved.
//

#ifndef StateTransition_hpp
#define StateTransition_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

class StateTransition {
private:
    int currentState;
    char input;
    char output;
    char dir;
    int next;
public:
    StateTransition();
    StateTransition(std::vector<std::string> s);
    ~StateTransition();
    bool Move(std::string &tape, std::string &currentState, size_t &pos);
};

#endif /* StateTransition_hpp */
