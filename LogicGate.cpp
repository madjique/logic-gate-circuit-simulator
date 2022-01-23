#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#include "Gate.hpp"
#include "LogicGate.hpp"
#include "Utils.hpp"

using namespace std;

LogicGate::LogicGate(Gate *gate1p, Gate *gate2p) : Gate(3)
{
    gate1 = gate1p;
    gate2 = gate2p;
}

LogicGate::LogicGate(Gate *gate1p) : Gate(2)
{
    gate1 = gate1p;
}

void LogicGate::simulate()
{
    gate1->update();
    gate1->simulate();
    if (type == 3)
    {
        gate2->update();
        gate2->simulate();
    }
    update();
    Utils::DrawSimulation(this);
}

void LogicGate::reset()
{
    value = 0;
    gate1->reset();
    if (type == 3)
        gate2->reset();
}

Gate *LogicGate::getGate()
{
    return this;
}

Gate *LogicGate::getGate1()
{
    return gate1;
}

Gate *LogicGate::getGate2()
{
    return gate2;
}

// GATES IMPLEMTATION

/*Negate*/
NeGate::NeGate(Gate *gate1p) : LogicGate(gate1p) { name = "neg"; };
bool NeGate::calculate()
{
    return (!gate1->calculate());
}
void NeGate::update()
{
    value = !gate1->getValue();
}

/*Orgate*/
OrGate::OrGate(Gate *gate1p, Gate *gate2p) : LogicGate(gate1p, gate2p) { name = "or"; };
bool OrGate::calculate()
{
    return (gate1->calculate() | gate2->calculate());
}
void OrGate::update()
{
    value = gate1->getValue() | gate2->getValue();
}

/*Norgate*/
NorGate::NorGate(Gate *gate1p, Gate *gate2p) : LogicGate(gate1p, gate2p) { name = "nor"; };
bool NorGate::calculate()
{
    return !(gate1->calculate() | gate2->calculate());
}
void NorGate::update()
{
    value = !(gate1->getValue() | gate2->getValue());
}

/*Andgate*/
AndGate::AndGate(Gate *gate1p, Gate *gate2p) : LogicGate(gate1p, gate2p) { name = "and"; };
bool AndGate::calculate()
{
    return (gate1->calculate() & gate2->calculate());
}
void AndGate::update()
{
    value = (gate1->getValue() & gate2->getValue());
}

/*Nandgate*/
NandGate::NandGate(Gate *gate1p, Gate *gate2p) : LogicGate(gate1p, gate2p) { name = "nand"; };
bool NandGate::calculate()
{
    return !(gate1->calculate() & gate2->calculate());
}
void NandGate::update()
{
    value = !(gate1->getValue() & gate2->getValue());
}

/*Xorgate*/
XorGate::XorGate(Gate *gate1p, Gate *gate2p) : LogicGate(gate1p, gate2p) { name = "xor"; };
bool XorGate::calculate()
{
    return (gate1->calculate() ^ gate2->calculate());
}
void XorGate::update()
{
    value = (gate1->getValue() ^ gate2->getValue());
}

/*Nxor*/
NxorGate::NxorGate(Gate *gate1p, Gate *gate2p) : LogicGate(gate1p, gate2p) { name = "nxor"; };
bool NxorGate::calculate()
{
    return !(gate1->calculate() ^ gate2->calculate());
}
void NxorGate::update()
{
    value = !(gate1->getValue() ^ gate2->getValue());
}