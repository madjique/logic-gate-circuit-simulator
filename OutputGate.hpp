#ifndef OUTPUTGATE
#define OUTPUTGATE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "Gate.hpp"

using namespace std;

class OutputGate : public Gate
{
private:
    Gate *gate;

public:
    OutputGate(Gate *gate1p, string nom);
    bool calculate();
    void update();
    void simulate();
    void reset();
    Gate *getGate();
    
    // avoidance of virtual
    Gate *getGate1();
    Gate *getGate2();
};

#endif