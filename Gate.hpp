#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


class Gate {
    protected:
        int type = 0 ;
        
        // 0  : default
        // 1  : Input Gate
        // 2  : 1arg Gate
        // 3  : 2arg Gate
        // 4  : Output Gate

        string name = "default";
        bool value = 0 ;
    public :
        Gate(){}
        Gate(int typep);
        virtual bool calculate()  = 0 ;
        virtual void simulate() = 0 ;
        virtual void update()  = 0 ;
        void reset();
        int getType();
        bool getValue();
        string getName();
        virtual Gate* getGate()  = 0 ;
        virtual Gate* getGate1() = 0 ;
        virtual Gate* getGate2() = 0 ;
};
