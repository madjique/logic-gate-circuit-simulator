#ifndef UTILS
#define UTILS

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#include "Gate.hpp"
#include "InputGate.hpp"
#include "OutputGate.hpp"
#include "LogicGate.hpp"

class Utils{
    
public :

static map<string,InputGate*> inputGates ;

static void SimulationWait();
static void DrawSimulation(Gate* gate);
static void Draw(Gate* gate);
static string GateToText(Gate* gate);
static string getGateNameFromText(string s);
static string getGateFirstMemberFromText(string s);
static string getGateSecondMemberFromText(string s);
static Gate* getLogicGate(string str,Gate* gate1,Gate* gate2);
static InputGate* getInputInstance(string letter);
static Gate* TextToGate(string expression);
static void Simulation(OutputGate* gate);
static void TextToFile(string expression);
static string FileToText(string filename);

};


#endif /* UTILS */