#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "Gate.hpp"
#include "Utils.hpp"
#include "OutputGate.hpp"
#include "InputGate.hpp"
#include "LogicGate.hpp"

using namespace std;

int main(){
    cout << "Test" << endl ;
    
    //  Exemple de sujet 
    InputGate *a = new InputGate ("a");
    InputGate *b = new InputGate ("b");
    Gate * or1 = new NeGate(a);
    Gate * or2 = new OrGate(or1,b);
    Gate * and1 = new AndGate (a,b);
    Gate * and2 = new XorGate (or2 , and1 );
    OutputGate *A = new OutputGate ( and2 );
    a->setValue(true);
    b->setValue(true);
    string text =  Utils::GateToText(A)  ;
    cout << text << endl ;
    cout << Utils::GateToText(Utils::TextToGate(text)) << endl ;
    Utils::Simulation(A);
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

    return 0;
}