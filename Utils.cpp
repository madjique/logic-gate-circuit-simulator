#include "Utils.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <ncurses.h>

#include "Gate.hpp"
#include "InputGate.hpp"
#include "OutputGate.hpp"
#include "LogicGate.hpp"
#include "OneArgGate.hpp"
#include "TwoArgGate.hpp"

using namespace std;

//init static variable
map<string, InputGate *> Utils::inputGates = map<string, InputGate *>();

string Utils::toUpper(string data)
{
    string s = data;
    for_each(s.begin(), s.end(), [](char &c)
             { c = ::toupper(c); });
    return s;
}

void Utils::SimulationWait()
{
    string cmd;
    cout << "type anything to continue the simulation" << endl;
    cin >> cmd;
}

// TODO : SHOW the state with the currect value from the sub tree that Gate comes from
void Utils::DrawSimulation(Gate *gate)
{
    SimulationWait();
    cout << "Drawing" << endl;
}

void Utils::Draw(Gate *gate, int positionY, int positionX)
{
    if (gate->getType() == 4)
    {
        Utils::Draw(gate->getGate(), positionY - 3, positionX);
        gate->getGate()->update();
        move(positionY, positionX);
        // printw(gate->getName().data());
        printw(gate->getGate()->getValue() ? "++" : "**");
        move(positionY - 1, positionX);
        printw("|");
        move(positionY - 2, positionX - 1);
        printw(Utils::toUpper(gate->getGate()->getName()).data());
    }
    else if (gate->getType() == 3)
    {

        if (gate->getGate1()->getType() != 1)
        {
            Utils::Draw(gate->getGate1(), positionY - 4, positionX - 3);
            move(positionY - 3, positionX - 3);
            printw(Utils::toUpper(gate->getGate1()->getName()).data());
        }
        else
        {
            Utils::Draw(gate->getGate1(), positionY - 3, positionX - 2);
        }
        if (gate->getGate2()->getType() != 1)
        {
            Utils::Draw(gate->getGate2(), positionY - 4, positionX + 3);
            move(positionY - 3, positionX + 2);
            printw(Utils::toUpper(gate->getGate2()->getName()).data());
        }
        else
        {
            Utils::Draw(gate->getGate2(), positionY - 3, positionX + 2);
        }

        move(positionY, positionX - 1);
        printw("|");
        move(positionY, positionX + 1);
        printw("|");

        move(positionY - 1, positionX - 2);
        gate->getGate1()->update();
        printw(gate->getGate1()->getValue() ? "++" : "**");
        gate->getGate2()->update();
        move(positionY - 1, positionX + 1);
        printw(gate->getGate2()->getValue() ? "++" : "**");

        move(positionY - 2, positionX - 2);
        printw("|");
        move(positionY - 2, positionX + 2);
        printw("|");
    }
    else if (gate->getType() == 2)
    {
        move(positionY, positionX);
        printw("|");
        move(positionY - 1, positionX);
        gate->getGate1()->update();
        printw(gate->getGate1()->getValue() ? "++" : "**");
        move(positionY - 2, positionX);
        printw("|");
        move(positionY - 3, positionX);
        printw(Utils::toUpper(gate->getGate1()->getName()).data());
    }
    else if (gate->getType() == 1)
    {
        move(positionY, positionX);
        printw(Utils::toUpper(gate->getName()).data());
    }
}

string Utils::GateToText(Gate *gate)
{
    if (gate->getType() == 0 || gate->getType() == 1)
        return gate->getName();
    else if (gate->getType() == 4)
        return GateToText(gate->getGate());
    else if (gate->getType() == 2)
        return gate->getName() + "(" + GateToText(gate->getGate1()) + ")";
    else if (gate->getType() == 3)
        return gate->getName() + "(" + GateToText(gate->getGate1()) + "," + GateToText(gate->getGate2()) + ")";
}

string Utils::getGateNameFromText(string s)
{
    string op = "";
    for (auto it = s.cbegin(); it != s.cend(); ++it)
    {
        if (*it == '(')
            break;
        else
            op += *it;
    }
    return op;
}

string Utils::getGateFirstMemberFromText(string s)
{
    string member = "";
    bool start = false;
    int parenthesis = 0;
    for (auto it = s.cbegin(); it != s.cend(); ++it)
    {
        if (!start)
        {
            if (*it == '(')
                start = true;
        }
        else
        {
            if (*it == '(')
                parenthesis++;
            else if (*it == ')')
                parenthesis--;
            else if (*it == ',' & parenthesis == 0)
                break;
            member += *it;
        }
    }
    //case only one member
    if (parenthesis == -1)
        member.pop_back();
    return member;
}

string Utils::getGateSecondMemberFromText(string s)
{
    string member = "";
    bool start = false;
    int parenthesis = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it)
    {
        if (!start)
        {
            if (*it == ')')
                start = true;
        }
        else
        {
            if (*it == ')')
                parenthesis++;
            else if (*it == '(')
                parenthesis--;
            else if (*it == ',' & parenthesis == 0)
                break;
            member += *it;
        }
    }
    reverse(member.begin(), member.end());
    return member;
}

Gate *Utils::getLogicGate(string str, Gate *gate1, Gate *gate2)
{
    if (str == "or")
        return new OrGate(gate1, gate2);
    else if (str == "and")
        return new AndGate(gate1, gate2);
    else if (str == "nor")
        return new NorGate(gate1, gate2);
    else if (str == "nand")
        return new NandGate(gate1, gate2);
    else if (str == "xor")
        return new XorGate(gate1, gate2);
    else if (str == "nxor")
        return new NxorGate(gate1, gate2);
    else if (str == "neg")
        return new NeGate(gate1);
    return nullptr;
}

InputGate *Utils::getInputInstance(string letter)
{
    if (!inputGates.count(letter))
        inputGates.insert({letter, new InputGate(letter)});
    return inputGates.at(letter);
}

Gate *Utils::TextToGate(string expression)
{
    if (expression.length() <= 1)
        return getInputInstance(expression);
    else
    {
        string operation = getGateNameFromText(expression);
        string firstMember = getGateFirstMemberFromText(expression);
        if (operation == "neg")
        {
            return getLogicGate(operation, TextToGate(firstMember), NULL);
        }
        else
        {
            string secondtMember = getGateSecondMemberFromText(expression);
            return getLogicGate(operation, TextToGate(firstMember), TextToGate(secondtMember));
        }
    }
}

void Utils::Simulation(OutputGate *gate)
{
    string cmd;
    while (true)
    {
        cout << "type anything to start the simulation" << endl;
        cout << "type 'stop' to end the simulation" << endl;
        cin >> cmd;
        if (cmd == "stop")
            break;
        else
        {
            gate->simulate();
        }
    }
}

void Utils::TextToFile(string expression)
{
    ofstream myfile;
    myfile.open("example.txt");
    myfile << expression + "\n";
    myfile.close();
}

string Utils::FileToText(string filename)
{
    string line = "";
    ifstream myfile(filename);
    if (myfile.is_open())
    {
        getline(myfile, line);
        myfile.close();
        return line;
    }
    else
        cout << "Impossible d'ouvrir le fichier";
    return line;
}