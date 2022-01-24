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
    void simulate(int positionY, int positionX);
    void reset();
    Gate *getGate();
    Gate *getGate1();
    Gate *getGate2();
};

#endif