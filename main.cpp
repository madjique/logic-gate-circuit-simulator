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
    // A->calculate();
    string text = Utils::GateToText(A);
    printw(text.data());
    // printw(Utils::GateToText(Utils::TextToGate(text)).data());
    refresh();
    Utils::Draw(A, INITIAL_Y, INITIAL_X);
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