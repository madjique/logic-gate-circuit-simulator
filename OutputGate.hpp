#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "Gate.hpp"
#include "Utils.hpp"

using namespace std;

class OutputGate : public Gate{
    private :
        Gate* gate;
    public : 
        OutputGate(Gate* gate1p);
        bool calculate();
        void update();
        void simulate();
        void reset();
        Gate* getGate();
        Gate* getGate1();
        Gate* getGate2();
};
