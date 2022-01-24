#ifndef LOGICGATE
#define LOGICGATE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

#include "Gate.hpp"
class LogicGate : public Gate
{
public:
    LogicGate(int type);
    virtual bool calculate() = 0;
    virtual void update() = 0;
    virtual void simulate(int positionY, int positionX) = 0;
    virtual Gate *getGate() = 0;
    virtual Gate *getGate1() = 0;
    virtual Gate *getGate2() = 0;
};

#endif