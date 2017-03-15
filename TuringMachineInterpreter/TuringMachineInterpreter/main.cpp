//
//  main.cpp
//  TuringMachineInterpreter
//
//  Created by Dana Zagar on 2017-03-14.
//  Copyright © 2017 Dana Zagar. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "StateTransition.hpp"

int main(int argc, const char * argv[]) {
    
    std::string inputfilename = "input.txt";
    std::string outputfilename = "output.txt";
    
    std::ifstream inputFile(inputfilename);     //input file stream
    std::ofstream outputFile(outputfilename);   //output file stream
    std::vector<std::string> fmtLine;           //formatted line (without whitespaces)
    std::vector<std::string> finalStates;       //final states
    std::vector<StateTransition*> transitions;  //transitions
    StateTransition* transition;                //single transition
    std::vector<std::string> tapes;             //tapes
    std::string currentState;                   //current state
    bool accept = false;                        //is the machine accepting?
    
    std::string input;
    
    //Loop through each line of the input file
    while (getline(inputFile, input)){
        std::string s = "";
        fmtLine.clear();
        //Loop through characters of line, add inputs to vector
        for (int i = 0; i < input.length(); i++){
            if (input[i] == ' '){
                if (s == "") continue;
                fmtLine.push_back(s);
                s = "";
            } else {
                s += input[i];
            }
        }
        fmtLine.push_back(s);
        
        //Find i (input tape)
        if (std::find(fmtLine.begin(), fmtLine.end(), "i") != fmtLine.end()){
            //Add '_' to start and end of new tape
            std::string newTape = "_";
            //Build new tape string
            for (int i = 0; i < fmtLine.size(); i++){
                if (fmtLine[i] == "i") continue;
                newTape += fmtLine[i];
            }
            newTape += "_";
            //Add tape to tapes vector
            tapes.push_back(newTape);
            continue;
        }
        //Find f (final states)
        else if (std::find(fmtLine.begin(), fmtLine.end(), "f") != fmtLine.end()){
            //Add all final states to final states vector
            for (int i = 0; i < fmtLine.size(); i++){
                if (fmtLine[i] == "f") continue;
                finalStates.push_back(fmtLine[i]);
            }
            continue;
        }
        //Find t (transition)
        else if (std::find(fmtLine.begin(), fmtLine.end(), "t") != fmtLine.end()){
            //Add transition to transitions ptr vector
            transition = new StateTransition(fmtLine);
            transitions.push_back(transition);
            continue;
        }
    }
    
    //Start iterating through each tape
    for (int i = 0; i < tapes.size(); i++){
        //Start at start state 0, not accepting and thus far cannot transition
        currentState = "0";
        accept = false;
        bool canTransition = false;
        
        size_t head = 1;    //Location of head, starts at 1 (first element of tape)
        
        //Iterate through tape
        while(head < tapes[i].length()){
            //Check for transitions
            for (int j = 0; j < transitions.size(); j++){
                //Check if transition exists; if one is found continue
                canTransition = transitions[j]->Move(tapes[i], currentState, head);
                if (canTransition) break;
            }
            //If no transition found, break
            if (!canTransition) break;
        }
        
        //Check if current state is any of the defined final states
        for (int k = 0; k < finalStates.size(); k++){
            if (currentState == finalStates[k]){
                accept = true;
                break;
            }
        }
        
        //If accept is true, "ACCEPT" otherwise "REJECT"
        if (accept){
            outputFile << tapes[i] << std::endl << "ACCEPT!" << std::endl;
        } else {
            outputFile << tapes[i] << std::endl << "REJECT!" << std::endl;
        }
    }
    std::string close;
    std::cout << "Press any key to exit, dawg.";
    std::getline(std::cin, close);
    return 0;
}

