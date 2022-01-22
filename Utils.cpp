#include "Utils.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>


#include "Gate.hpp"
#include "InputGate.hpp"
#include "OutputGate.hpp"
#include "LogicGate.hpp"

using namespace std;


//init static variable
map<string,InputGate*> Utils::inputGates = map<string,InputGate*>() ;

void Utils::SimulationWait(){
    string cmd ;
    cout << "type anything to continue the simulation" << endl ;
    cin >> cmd ;
}

// TODO : SHOW the state with the currect value from the sub tree that Gate comes from
void Utils::DrawSimulation(Gate* gate){
    SimulationWait() ;
    cout << "Drawing" << endl ;
}

// TODO : SHOW the state with the currect value from the sub tree that Gate comes from
void Utils::Draw(Gate* gate){
    SimulationWait() ;
    cout << "Drawing" << endl ;
}


string Utils::GateToText(Gate* gate){
    if (gate->getType() == 0 || gate->getType() == 1 )
        return gate->getName() ;
    else if (gate->getType() == 4)
        return GateToText(gate->getGate()) ;
    else if (gate->getType() == 2)
        return gate->getName() + "(" + GateToText(gate->getGate1()) + ")" ;
    else if (gate->getType() == 3)
        return gate->getName() + "(" + GateToText(gate->getGate1()) + "," + GateToText(gate->getGate2()) + ")" ;
}

string Utils::getGateNameFromText(string s){
    string op = "" ;
    for (auto it = s.cbegin() ; it != s.cend(); ++it) {
        if (*it == '(')
            break ;
        else
            op+= *it ;
    } 
    return op ;
}

string Utils::getGateFirstMemberFromText(string s){
    string member = "" ;
    bool start = false ;
    int parenthesis = 0 ;
    for (auto it = s.cbegin() ; it != s.cend(); ++it) {
        if (!start){
            if (*it == '(') start = true ;
        }
        else{
            if (*it == '(') parenthesis++ ;
            else if  (*it == ')') parenthesis-- ;
            else if (*it == ',' & parenthesis == 0)
                break ;    
            member+= *it ;
        }
    } 
    //case only one member
    if( parenthesis == -1 ) 
        member.pop_back();
    return member ;
}

string Utils::getGateSecondMemberFromText(string s){
    string member = "" ;
    bool start = false ;
    int parenthesis = 0 ;
    for (auto it = s.rbegin() ; it != s.rend(); ++it) {
        if (!start){
            if (*it == ')') start = true ;
        }
        else{
            if (*it == ')') parenthesis++ ;
            else if  (*it == '(') parenthesis-- ;
            else if (*it == ',' & parenthesis == 0)
                break ;    
            member+= *it ;
        }
    } 
    reverse(member.begin(),member.end());
    return member ;
}

Gate* Utils::getLogicGate(string str,Gate* gate1,Gate* gate2){
    if (str == "or") 
            return new OrGate(gate1,gate2);
    else if (str == "and" )
            return new AndGate(gate1,gate2);
    else if (str == "nor" )
            return new NorGate(gate1,gate2);
    else if (str == "nand" ) 
            return new NandGate(gate1,gate2);
    else if (str == "xor" ) 
            return  new XorGate(gate1,gate2);
    else if (str == "nxor" ) 
            return  new NxorGate(gate1,gate2);
    else if (str == "negate" ) 
            return  new NeGate(gate1);
    return nullptr ;
}

InputGate* Utils::getInputInstance(string letter){
    if(!inputGates.count(letter))
        inputGates.insert({letter,new InputGate(letter)});
    return inputGates.at(letter) ;
}

Gate* Utils::TextToGate(string expression){
    if (expression.length() <= 1)
        return getInputInstance(expression);
    else {
        string operation = getGateNameFromText(expression) ;
        string firstMember = getGateFirstMemberFromText(expression);
        if (operation == "negate"){
            return getLogicGate(operation,TextToGate(firstMember),NULL);
        }
        else{
            string secondtMember = getGateSecondMemberFromText(expression);
            return getLogicGate(operation,TextToGate(firstMember),TextToGate(secondtMember));
        }
    }
}

void Utils::Simulation(OutputGate* gate){
    string cmd ;
    while(true)
    {
        cout << "type anything to start the simulation" << endl ;
        cout << "type 'stop' to end the simulation" << endl ;
        cin >> cmd ;
        if (cmd == "stop")
            break ;
        else{
            gate->simulate() ;
        }
    }
}

void Utils::TextToFile(string expression){
    ofstream myfile;
    myfile.open ("example.txt");
    myfile << expression + "\n";
    myfile.close();
}

string Utils::FileToText(string filename){
    string line = "";
    ifstream myfile (filename);
    if (myfile.is_open()) {
        getline (myfile,line) ;
        myfile.close();
        return line ;
    }
    else cout << "Impossible d'ouvrir le fichier"; 
    return line ;
}
