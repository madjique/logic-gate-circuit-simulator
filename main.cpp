#include <iostream>
#include <string>

using namespace std;

class Gate {
    protected:
        int type = 0 ;
        // 0  : default
        // 1  : Input Gate
        // 2  : Operation Gate
        // 3  : Output Gate
    public :
    
        Gate(){}
        Gate(int typep){ 
            type = typep ;
        }
        virtual bool calculate()  = 0 ;

};


class InputGate : public Gate{
    private :
        string name = "default" ;
        bool value = 0 ;
    public : 
        InputGate(string namep):Gate(1){
            name = namep ;
        }
        void setValue(bool valuep){
            value = valuep ;
        }
        bool calculate(){
            return value;
        }
};

class OutputGate : public Gate{
    Gate* gate;
    public : 
        OutputGate(Gate* gate1p):Gate(3){
            gate = gate1p ;
        }
        bool calculate(){
            return gate->calculate() ;
        }
};

class LogicGate : public Gate {
    protected :
        Gate* gate1,*gate2;
    public : 
        LogicGate(Gate* gate1p,Gate* gate2p ):Gate(2){
            gate1 = gate1p ;
            gate2 = gate2p ;
        } 
        LogicGate(Gate* gate1p ):Gate(2){
            gate1 = gate1p ;
        }
        virtual bool calculate()  = 0 ;
};

class NeGate : public LogicGate{
    public : 
        NeGate(Gate* gate1p):LogicGate(gate1p){};
        bool calculate(){
            return (!gate1->calculate()) ;
        }
};

class OrGate : public LogicGate{
    public : 
        OrGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){};
        bool calculate(){
            return (gate1->calculate() | gate2->calculate()) ;
        }
};

class NorGate : public LogicGate{
    public : 
        NorGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){};
        bool calculate(){
            return !(gate1->calculate() | gate2->calculate()) ;
        }
};


class AndGate : public LogicGate{
    public : 
        AndGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){};
        bool calculate(){
            return (gate1->calculate() & gate2->calculate()) ;
        }
};

class NandGate : public LogicGate{
    public : 
        NandGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){};
        bool calculate(){
            return !(gate1->calculate() & gate2->calculate()) ;
        }
};

class XorGate : public LogicGate{
    public : 
        XorGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){};
        bool calculate(){
            return (gate1->calculate() ^ gate2->calculate()) ;
        }
};

class NxorGate : public LogicGate{
    public : 
        NxorGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){};
        bool calculate(){
            return !(gate1->calculate() ^ gate2->calculate()) ;
        }
};

int main(){
    cout << "Test" << endl ;
    
    // Exemple de sujet 
    // InputGate *a = new InputGate ("a");
    // InputGate *b = new InputGate ("b");
    // Gate * or1 = new OrGate (a,b);
    // Gate * and1 = new AndGate (a,b);
    // Gate * and2 = new XorGate (or1 , and1 );
    // OutputGate *A = new OutputGate ( and2 );
    // a->setValue(false);
    // b->setValue(true);
    // cout << A->calculate() << endl ;

    // Mon exemple
    InputGate a("a");
    InputGate b("b");
    a.setValue(true);
    b.setValue(false);
    OrGate orgate(&a,&b);
    OutputGate Aout( &orgate );

    cout << Aout.calculate() << endl ;

    return 0;
}