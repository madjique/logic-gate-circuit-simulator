#ifndef ONEGATE
#define ONEGATE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#include "LogicGate.hpp"

class OneArgGate : public LogicGate
{
protected:
    Gate *gate1;

public:
    OneArgGate(Gate *gate1p);
    void simulate(int positionY, int positionX);
    void reset();
    virtual bool calculate() = 0;
    virtual void update() = 0;
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