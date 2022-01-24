#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#include "LogicGate.hpp"
#include "OneArgGate.hpp"
#include "Utils.hpp"

using namespace std;

OneArgGate::OneArgGate(Gate *gate1p) : LogicGate(2)
{
    gate1 = gate1p;
}

void OneArgGate::simulate(int positionY, int positionX)
{
    gate1->update();
    gate1->simulate(positionY - 3, positionX);
    update();
    Utils::DrawSimulation(this, positionY, positionX);
}

void OneArgGate::reset()
{
    value = 0;
    gate1->reset();
}

Gate *OneArgGate::getGate()
{
    return gate1;
}

Gate *OneArgGate::getGate1()
{
    return gate1;
}

Gate *OneArgGate::getGate2()
{
    return gate1;
}
// GATES IMPLEMTATION

/*Negate*/
NeGate::NeGate(Gate *gate1p) : OneArgGate(gate1p) { name = "neg"; };

bool NeGate::calculate()
{
    return (!gate1->calculate());
}

void NeGate::update()
{
    value = !gate1->getValue();
}
