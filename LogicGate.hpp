#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "Gate.hpp"
#include "Utils.hpp"

using namespace std;


class LogicGate : public Gate {
    protected :
        Gate* gate1,*gate2;
    public : 
        // 2 arg gate
        LogicGate(Gate* gate1p,Gate* gate2p );
        // 1 arg gate
        LogicGate(Gate* gate1p );
        virtual bool calculate()  = 0 ;
        virtual void update()  = 0 ;
        void simulate();
        void reset();
        Gate* getGate();
        Gate* getGate1();
        Gate* getGate2();

};

class NeGate : public LogicGate{
    public : 
        NeGate(Gate* gate1p);
        bool calculate();
        void update();
};

class OrGate : public LogicGate{
    public : 
        OrGate(Gate* gate1p,Gate* gate2p);
        bool calculate();
        void update();
};

class NorGate : public LogicGate{
    public : 
        NorGate(Gate* gate1p,Gate* gate2p);
        bool calculate();
        void update();
};


class AndGate : public LogicGate{
    public : 
        AndGate(Gate* gate1p,Gate* gate2p);
        bool calculate();
        void update();
};

class NandGate : public LogicGate{
    public : 
        NandGate(Gate* gate1p,Gate* gate2p);
        bool calculate();
        void update();
};

class XorGate : public LogicGate{
    public : 
        XorGate(Gate* gate1p,Gate* gate2p);
        bool calculate();
        void update();
};

class NxorGate : public LogicGate{
    public : 
        NxorGate(Gate* gate1p,Gate* gate2p);
        bool calculate();
        void update();
};
