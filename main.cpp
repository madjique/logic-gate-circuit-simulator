#include <iostream>
#include <string>

using namespace std;

class Gate {
    protected:
        int type = 0 ;
        string name = "default";
        // 0  : default
        // 1  : Input Gate
        // 2  : 1arg Gate
        // 3  : 2arg Gate
        // 4  : Output Gate
    public :
    
        Gate(){}
        Gate(int typep){ 
            type = typep ;
        }
        virtual bool calculate()  = 0 ;
        virtual Gate& getGate()  = 0 ;
        virtual Gate& getGate1() = 0 ;
        virtual Gate& getGate2() = 0 ;
        
        string getName(){
            return name ;
        }
        int getType(){
            return type ;
        }

};


class InputGate : public Gate{
    private :
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
        Gate& getGate() {
            return *this ;
        } ;
        Gate& getGate1() {
            return *this ;
        };
        Gate& getGate2() {
            return *this ;
        } ;
};

class OutputGate : public Gate{
    Gate* gate;
    public : 
        OutputGate(Gate* gate1p):Gate(4){
            gate = gate1p ;
        }
        bool calculate(){
            return gate->calculate() ;
        }
        Gate& getGate(){
            return *gate ;
        }
        Gate& getGate1() {
            return *this ;
        };
        Gate& getGate2() {
            return *this ;
        } ;
        
};

class LogicGate : public Gate {
    protected :
        Gate* gate1,*gate2;
    public : 
        // 2 arg gate
        LogicGate(Gate* gate1p,Gate* gate2p ):Gate(3){
            gate1 = gate1p ;
            gate2 = gate2p ;
        } 
        // 1 arg gate
        LogicGate(Gate* gate1p ):Gate(2){
            gate1 = gate1p ;
        }
        virtual bool calculate()  = 0 ;

        Gate& getGate(){
            return *this ;
        }

        Gate& getGate1(){
            return *gate1 ;
        }
        
        Gate& getGate2(){
            return *gate2 ;
        }

};

class NeGate : public LogicGate{
    public : 
        NeGate(Gate* gate1p):LogicGate(gate1p){ name = "negate"; };
        bool calculate(){
            return (!gate1->calculate()) ;
        }
};

class OrGate : public LogicGate{
    public : 
        OrGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "or"; };
        bool calculate(){
            return (gate1->calculate() | gate2->calculate()) ;
        }
};

class NorGate : public LogicGate{
    public : 
        NorGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "nor"; };
        bool calculate(){
            return !(gate1->calculate() | gate2->calculate()) ;
        }
};


class AndGate : public LogicGate{
    public : 
        AndGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "and"; };
        bool calculate(){
            return (gate1->calculate() & gate2->calculate()) ;
        }
};

class NandGate : public LogicGate{
    public : 
        NandGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "nand"; };
        bool calculate(){
            return !(gate1->calculate() & gate2->calculate()) ;
        }
};

class XorGate : public LogicGate{
    public : 
        XorGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "xor"; };
        bool calculate(){
            return (gate1->calculate() ^ gate2->calculate()) ;
        }
};

class NxorGate : public LogicGate{
    public : 
        NxorGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "nxor"; };
        bool calculate(){
            return !(gate1->calculate() ^ gate2->calculate()) ;
        }
};


string GateToText(Gate& gate){
    if (gate.getType() == 0 || gate.getType() == 1 )
        return gate.getName() ;
    else if (gate.getType() == 4)
        return GateToText(gate.getGate()) ;
    else if (gate.getType() == 2)
        return gate.getName() + "(" + GateToText(gate.getGate1()) + ")" ;
    else if (gate.getType() == 3)
        return gate.getName() + "(" + GateToText(gate.getGate1()) + "," + GateToText(gate.getGate2()) + ")" ;
}


// Gate TextToGate(string expression){

// }


// void TextToFile(string gate){

// }

// Gate TextToGate(string expression){

// }

// void Draw(OutputGate& gate){
    
// }

int main(){
    cout << "Test" << endl ;
    
    //  Exemple de sujet 
    InputGate *a = new InputGate ("a");
    InputGate *b = new InputGate ("b");
    Gate * or1 = new OrGate (a,b);
    Gate * and1 = new AndGate (a,b);
    Gate * and2 = new XorGate (or1 , and1 );
    OutputGate *A = new OutputGate ( and2 );
    a->setValue(false);
    b->setValue(true);
    cout << GateToText(*A) << endl ;

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