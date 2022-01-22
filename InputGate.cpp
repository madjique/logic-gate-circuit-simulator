#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "Gate.hpp"
#include "Utils.hpp"
#include "InputGate.hpp"

using namespace std;

InputGate::InputGate(string namep):Gate(1){
    name = namep ;
} ;

void InputGate::setValue(bool valuep){
    value = valuep ;
} ;

bool InputGate::calculate(){
    return value;
} ;

void InputGate::update(){
    
} ;

void InputGate::simulate(){
    Utils::DrawSimulation(this);
} ;

Gate* InputGate::getGate() {
    return this ;
} ;

Gate* InputGate::getGate1() {
    return this ;
} ;

Gate* InputGate::getGate2() {
    return this ;
} ;
