#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "Gate.hpp"

using namespace std;

Gate::Gate(){}

Gate::Gate(int typep){ 
    type = typep ;
}

string Gate::getName(){
    return name ;
}

int Gate::getType(){
    return type ;
}

void Gate::reset(){
    value = 0;
}

bool Gate::getValue(){
    return value ;
}
