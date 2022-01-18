#include <iostream>
#include <string>

using namespace std;

class Gate {
    protected:
        int type = 0 ;
        string name = "default";
        bool value = 0 ;
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
        bool getValue(){
            return value ;
        }

};


class InputGate : public Gate{
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
        virtual void update()  = 0 ;

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
        void update(){
            value = !gate1->getValue() ;
        }
};

class OrGate : public LogicGate{
    public : 
        OrGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "or"; };
        bool calculate(){
            return (gate1->calculate() | gate2->calculate()) ;
        }
        void update(){
            value = gate1->getValue() | gate2->getValue() ;
        }
};

class NorGate : public LogicGate{
    public : 
        NorGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "nor"; };
        bool calculate(){
            return !(gate1->calculate() | gate2->calculate()) ;
        }
        void update(){
            value = !(gate1->getValue() | gate2->getValue()) ;
        }
};


class AndGate : public LogicGate{
    public : 
        AndGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "and"; };
        bool calculate(){
            return (gate1->calculate() & gate2->calculate()) ;
        }
        void update(){
            value = (gate1->getValue() & gate2->getValue()) ;
        }
};

class NandGate : public LogicGate{
    public : 
        NandGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "nand"; };
        bool calculate(){
            return !(gate1->calculate() & gate2->calculate()) ;
        }
        void update(){
            value = !(gate1->getValue() & gate2->getValue()) ;
        }
};

class XorGate : public LogicGate{
    public : 
        XorGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "xor"; };
        bool calculate(){
            return (gate1->calculate() ^ gate2->calculate()) ;
        }
        void update(){
            value = (gate1->getValue() ^ gate2->getValue()) ;
        }
};

class NxorGate : public LogicGate{
    public : 
        NxorGate(Gate* gate1p,Gate* gate2p):LogicGate(gate1p,gate2p){ name = "nxor"; };
        bool calculate(){
            return !(gate1->calculate() ^ gate2->calculate()) ;
        }
        void update(){
            value = !(gate1->getValue() ^ gate2->getValue()) ;
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

Gate* TextToGate(string expression){

}
// int findIndex(string str, int si, int ei)
// {
//     if (si > ei)
//         return -1;
//     stack<char> s;
//     for (int i = si; i <= ei; i++) {
//         if (str[i] == '(')
//             s.push(str[i]);
//         else if (str[i] == ')') {
//             if (s.top() == '(') {
//                 s.pop();
//                 if (s.empty())
//                     return i;
//             }
//         }
//     }
//     return -1;
// }

// Gate* treeFromString(string str, int si, int ei)
// {
//     // Base case
//     if (si > ei)
//         return NULL;
//     // new root
//     Gate* root = (str[si] - '0');
//     int index = -1;
//     // its complement ')'
//     if (si + 1 <= ei && str[si + 1] == '(')
//         index = findIndex(str, si + 1, ei);
//     // if index found
//     if (index != -1) {
//         // call for left subtree
//         root->left = treeFromString(str, si + 2, index - 1);
//         // call for right subtree
//         root->right
//             = treeFromString(str, index + 2, ei - 1);
//         return 
//     }
//     return getLogicGate( treeFromString(str, si + 2, index - 1));
// }


Gate* getLogicGate(string str,Gate* gate1,Gate* gate2){
    if (str == "or") 
            return new OrGate(gate1,gate2);
    else if (str == "and" )
            return new AndGate(gate1,gate2);
    else if (str == "nor" )
            return new NorGate(gate1,gate2);
    else if (str == "nand" ) 
            return new NandGate(gate1,gate2);
    else if (str == "xor" ) 
            return  new XorGate(gate1,gate2);
    else if (str == "nxor" ) 
            return  new NxorGate(gate1,gate2);
    else if (str == "negate" ) 
            return  new NeGate(gate1);
    return nullptr ;
}

// void TextToFile(string expression){

// }

// string FileToText(string filename){

// }

// void Draw(OutputGate* gate){
    
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
    a->setValue(true);
    b->setValue(true);
    cout << GateToText(*A) << endl ;
    cout << A->calculate() << endl ;  
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