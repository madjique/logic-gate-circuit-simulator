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
        move(positionY, positionX);
        // printw(gate->getName().data());
        printw("%d", gate->getValue() ? 1 : 0);
        move(positionY - 1, positionX);
        printw("|");
        move(positionY - 2, positionX - 1);
        printw(toUpper(gate->getGate()->getName()).data());
        draw(gate->getGate(), positionY - 3, positionX);
    }
    else if (gate->getType() == 3)
    {
        move(positionY, positionX - 3);
        printw("|");
        move(positionY, positionX + 3);
        printw("|");

        move(positionY - 1, positionX - 4);
        printw("%d", gate->getGate1()->getValue() ? 1 : 0);
        move(positionY - 1, positionX + 4);
        printw("%d", gate->getGate2()->getValue() ? 1 : 0);

        move(positionY - 2, positionX - 5);
        printw("|");
        move(positionY - 2, positionX + 5);
        printw("|");

        move(positionY - 3, positionX - 5);
        printw(toUpper(gate->getGate1()->getName()).data());
        move(positionY - 3, positionX + 5);
        printw(toUpper(gate->getGate2()->getName()).data());
        draw(gate->getGate1(), positionY - 4, positionX - 6);
        draw(gate->getGate2(), positionY - 4, positionX + 6);
    }
    else if (gate->getType() == 2)
    {
        move(positionY, positionX);
        printw("|");
        move(positionY - 1, positionX);
        printw("%d", gate->getGate1()->getValue() ? 1 : 0);
        move(positionY - 2, positionX);
        printw("|");
        move(positionY - 3, positionX);
        printw(toUpper(gate->getGate1()->getName()).data());
    }
    // int x = 0;
    // int y = 0;
    // move(INITIAL_Y - y, INITIAL_X - x);
    // y += 1;
    // printw(gate->getName().data());
    // move(INITIAL_Y - y, INITIAL_X - x);
    // printw("|");
    // y += 1;
    // x += 1;
    // move(INITIAL_Y - y, INITIAL_X - x);
    // printw(gate->getGate()->getName().data());
}

int main()
{
    initscr();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int INITIAL_X = xMax / 2;
    int INITIAL_Y = yMax / 2;

    //  Exemple de sujet
    InputGate *a = new InputGate("a");
    InputGate *b = new InputGate("b");
    Gate *or1 = new NeGate(a);
    Gate *or2 = new OrGate(or1, b);
    Gate *and1 = new AndGate(a, b);
    Gate *and2 = new XorGate(or2, and1);
    OutputGate *A = new OutputGate(and2, "A");
    a->setValue(true);
    b->setValue(false);
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