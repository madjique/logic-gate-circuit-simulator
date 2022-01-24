#ifndef INPUTGATE
#define INPUTGATE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "Gate.hpp"
#include "Utils.hpp"

using namespace std;

class InputGate : public Gate
{
public:
    InputGate(string namep);
    void setValue(bool valuep);
    bool calculate();
    void update();
    void simulate(int positionY, int positionX);

    // avoidance of virtual
    Gate *getGate();
    Gate *getGate1();
    Gate *getGate2();
};

#endif