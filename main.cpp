#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ncurses.h>
#include <bits/stdc++.h>

#include "Gate.hpp"
#include "Utils.hpp"
#include "InputGate.hpp"
#include "OutputGate.hpp"
#include "LogicGate.hpp"

using namespace std;

string toUpper(string data)
{
    string s = data;
    for_each(s.begin(), s.end(), [](char &c)
             { c = ::toupper(c); });
    return s;
}

void draw(Gate *gate, int positionY, int positionX)
{
    if (gate->getType() == 4)
    {
        draw(gate->getGate(), positionY - 3, positionX);
        gate->getGate()->update();
        move(positionY, positionX);
        // printw(gate->getName().data());
        printw(gate->getGate()->getValue() ? "++" : "**");
        move(positionY - 1, positionX);
        printw("|");
        move(positionY - 2, positionX - 1);
        printw(toUpper(gate->getGate()->getName()).data());
    }
    else if (gate->getType() == 3)
    {

        if (gate->getGate1()->getType() != 1)
        {
            draw(gate->getGate1(), positionY - 4, positionX - 3);
            move(positionY - 3, positionX - 3);
            printw(toUpper(gate->getGate1()->getName()).data());
        }
        else
        {
            draw(gate->getGate1(), positionY - 3, positionX - 2);
        }
        if (gate->getGate2()->getType() != 1)
        {
            draw(gate->getGate2(), positionY - 4, positionX + 3);
            move(positionY - 3, positionX + 2);
            printw(toUpper(gate->getGate2()->getName()).data());
        }
        else
        {
            draw(gate->getGate2(), positionY - 3, positionX + 2);
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
        printw(toUpper(gate->getGate1()->getName()).data());
    }
    else if (gate->getType() == 1)
    {
        move(positionY, positionX);
        // printw("|");
        // move(positionY - 1, positionX);
        // printw(gate->getGate1()->getValue() ? "++" : "**");
        // move(positionY - 2, positionX);
        // printw("|");
        // move(positionY - 3, positionX);
        printw(toUpper(gate->getName()).data());
    }
}

int main()
{
    initscr();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int INITIAL_X = xMax / 2;
    int INITIAL_Y = yMax - 5;

    //  Exemple de sujet
    InputGate *a = new InputGate("a");
    InputGate *b = new InputGate("b");
    // InputGate *d = new InputGate("d");

    Gate *or1 = new NeGate(a);
    Gate *or2 = new OrGate(a, b);
    // Gate *nand = new NandGate(or2, d);
    Gate *and1 = new AndGate(a, b);
    Gate *and2 = new XorGate(or2, and1);
    OutputGate *A = new OutputGate(and2, "A");
    a->setValue(true);
    b->setValue(true);
    // d->setValue(false);
    A->calculate();
    string text = Utils::GateToText(A);
    printw(text.data());
    // printw(Utils::GateToText(Utils::TextToGate(text)).data());
    refresh();
    draw(A, INITIAL_Y, INITIAL_X);
    refresh();

    // Utils::Simulation(A);
    // clear cache of input Instances
    Utils::inputGates.clear();

    A->reset();

    // Mon exemple
    // InputGate a("a");
    // InputGate b("b");
    // a.setValue(true);
    // b.setValue(false);
    // OrGate orgate(&a,&b);
    // OutputGate Aout( &orgate );
    // cout << GateToText(Aout) << endl ;
    // cout << Aout.calculate() << endl ;
    getch();
    endwin();
    return 0;
}