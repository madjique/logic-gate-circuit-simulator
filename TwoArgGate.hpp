#ifndef TWOGATE
#define TWOGATE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#include "LogicGate.hpp"

class TwoArgGate : public LogicGate
{
protected:
    Gate *gate1, *gate2;

public:
    TwoArgGate(Gate *gate1p, Gate *gate2p);
    void simulate(int positionY, int positionX);
    void reset();
    virtual bool calculate() = 0;
    virtual void update() = 0;
    Gate *getGate();
    Gate *getGate1();
    Gate *getGate2();
};

class OrGate : public TwoArgGate
{
public:
    OrGate(Gate *gate1p, Gate *gate2p);
    bool calculate();
    void update();
};

class NorGate : public TwoArgGate
{
public:
    NorGate(Gate *gate1p, Gate *gate2p);
    bool calculate();
    void update();
};

class AndGate : public TwoArgGate
{
public:
    AndGate(Gate *gate1p, Gate *gate2p);
    bool calculate();
    void update();
};

class NandGate : public TwoArgGate
{
public:
    NandGate(Gate *gate1p, Gate *gate2p);
    bool calculate();
    void update();
};

class XorGate : public TwoArgGate
{
public:
    XorGate(Gate *gate1p, Gate *gate2p);
    bool calculate();
    void update();
};

class NxorGate : public TwoArgGate
{
public:
    NxorGate(Gate *gate1p, Gate *gate2p);
    bool calculate();
    void update();
};

#endif