#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#include "Gate.hpp"
#include "TwoArgGate.hpp"
#include "Utils.hpp"

using namespace std;

TwoArgGate::TwoArgGate(Gate *gate1p, Gate *gate2p) : LogicGate(3)
{
    gate1 = gate1p;
    gate2 = gate2p;
}

void TwoArgGate::simulate()
{
    gate1->update();
    gate1->simulate();
    gate2->update();
    gate2->simulate();
    update();
    Utils::DrawSimulation(this);
}

void TwoArgGate::reset()
{
    value = 0;
    gate1->reset();
    gate2->reset();
}

Gate *TwoArgGate::getGate1()
{
    return gate1;
}

Gate *TwoArgGate::getGate2()
{
    return gate2;
}

// GATES IMPLEMTATION

/*Orgate*/
OrGate::OrGate(Gate *gate1p, Gate *gate2p) : TwoArgGate(gate1p, gate2p) { name = "or"; };
bool OrGate::calculate()
{
    return (gate1->calculate() | gate2->calculate());
}
void OrGate::update()
{
    value = gate1->getValue() | gate2->getValue();
}

/*Norgate*/
NorGate::NorGate(Gate *gate1p, Gate *gate2p) : TwoArgGate(gate1p, gate2p) { name = "nor"; };
bool NorGate::calculate()
{
    return !(gate1->calculate() | gate2->calculate());
}
void NorGate::update()
{
    value = !(gate1->getValue() | gate2->getValue());
}

/*Andgate*/
AndGate::AndGate(Gate *gate1p, Gate *gate2p) : TwoArgGate(gate1p, gate2p) { name = "and"; };
bool AndGate::calculate()
{
    return (gate1->calculate() & gate2->calculate());
}
void AndGate::update()
{
    value = (gate1->getValue() & gate2->getValue());
}

/*Nandgate*/
NandGate::NandGate(Gate *gate1p, Gate *gate2p) : TwoArgGate(gate1p, gate2p) { name = "nand"; };
bool NandGate::calculate()
{
    return !(gate1->calculate() & gate2->calculate());
}
void NandGate::update()
{
    value = !(gate1->getValue() & gate2->getValue());
}

/*Xorgate*/
XorGate::XorGate(Gate *gate1p, Gate *gate2p) : TwoArgGate(gate1p, gate2p) { name = "xor"; };
bool XorGate::calculate()
{
    return (gate1->calculate() ^ gate2->calculate());
}
void XorGate::update()
{
    value = (gate1->getValue() ^ gate2->getValue());
}

/*Nxor*/
NxorGate::NxorGate(Gate *gate1p, Gate *gate2p) : TwoArgGate(gate1p, gate2p) { name = "nxor"; };
bool NxorGate::calculate()
{
    return !(gate1->calculate() ^ gate2->calculate());
}
void NxorGate::update()
{
    value = !(gate1->getValue() ^ gate2->getValue());
}