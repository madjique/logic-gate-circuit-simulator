#ifndef ONEGATE
#define ONEGATE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#include "Gate.hpp"
#include "Utils.hpp"

#include "LogicGate.hpp"

class OneArgGate : public LogicGate
{
protected:
    Gate *gate1;

public:
    OneArgGate(Gate *gate1p);
    void simulate(int positionY, int positionX);
    void reset();
    Gate *getGate();
    Gate *getGate1();
    Gate *getGate2();
};

class NeGate : public OneArgGate
{
public:
    NeGate(Gate *gate1p);
    bool calculate();
    void update();
};

#endif