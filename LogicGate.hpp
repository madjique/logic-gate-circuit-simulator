#ifndef LOGICGATE
#define LOGICGATE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#include "Gate.hpp"
#include "Utils.hpp"

using namespace std;

class LogicGate : public Gate
{
public:
    LogicGate(int type);
    virtual bool calculate() = 0;
    virtual void update() = 0;
    virtual Gate *getGate();
    virtual Gate *getGate1();
    virtual Gate *getGate2();
};

#endif