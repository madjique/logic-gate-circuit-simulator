#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

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
        virtual Gate* getGate()  = 0 ;
        virtual Gate* getGate1() = 0 ;
        virtual Gate* getGate2() = 0 ;
        virtual void simulate() = 0 ;
        virtual void update()  = 0 ;

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

// TODO : SHOW the state with the currect value from the sub tree that Gate comes from
void Draw(Gate* gate){
    cout << "Drawing" << endl ;
}
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
        void update(){
           
        }
        void simulate(){
            Draw(this);
        }
        Gate* getGate() {
            return this ;
        } ;
        Gate* getGate1() {
            return this ;
        };
        Gate* getGate2() {
            return this ;
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
        void update(){
            value = gate->getValue() ;
        }
        void simulate(){
            gate->update();
            gate->simulate();
            //Draw(this);
        }
        Gate* getGate(){
            return gate ;
        }
        Gate* getGate1() {
            return this ;
        };
        Gate* getGate2() {
            return this ;
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
        void simulate(){
            gate1->update();
            gate1->simulate();
            if(gate2 != nullptr){
                gate2->update();
                gate2->simulate();
            }
            update();
            Draw(this);
        }
        Gate* getGate(){
            return this ;
        }

        Gate* getGate1(){
            return gate1 ;
        }
        
        Gate* getGate2(){
            return gate2 ;
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


string GateToText(Gate* gate){
    if (gate->getType() == 0 || gate->getType() == 1 )
        return gate->getName() ;
    else if (gate->getType() == 4)
        return GateToText(gate->getGate()) ;
    else if (gate->getType() == 2)
        return gate->getName() + "(" + GateToText(gate->getGate1()) + ")" ;
    else if (gate->getType() == 3)
        return gate->getName() + "(" + GateToText(gate->getGate1()) + "," + GateToText(gate->getGate2()) + ")" ;
}

string getGateNameFromText(string s){
    string op = "" ;
    for (auto it = s.cbegin() ; it != s.cend(); ++it) {
        if (*it == '(')
            break ;
        else
            op+= *it ;
    } 
    return op ;
}

string getGateFirstMemberFromText(string s){
    string member = "" ;
    bool start = false ;
    int parenthesis = 0 ;
    for (auto it = s.cbegin() ; it != s.cend(); ++it) {
        if (!start){
            if (*it == '(') start = true ;
        }
        else{
            if (*it == '(') parenthesis++ ;
            else if  (*it == ')') parenthesis-- ;
            else if (*it == ',' & parenthesis == 0)
                break ;    
            member+= *it ;
        }
    } 
    //case only one member
    if( parenthesis == -1 ) 
        member.pop_back();
    return member ;
}

string getGateSecondMemberFromText(string s){
    string member = "" ;
    bool start = false ;
    int parenthesis = 0 ;
    for (auto it = s.rbegin() ; it != s.rend(); ++it) {
        if (!start){
            if (*it == ')') start = true ;
        }
        else{
            if (*it == ')') parenthesis++ ;
            else if  (*it == '(') parenthesis-- ;
            else if (*it == ',' & parenthesis == 0)
                break ;    
            member+= *it ;
        }
    } 
    reverse(member.begin(),member.end());
    return member ;
}

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

// Global variable
// can make it static in InputGate class but we dont really need to do that
map<string,InputGate*> inputGates;

InputGate* getInputInstance(string letter){
    if(!inputGates.count(letter))
        inputGates.insert({letter,new InputGate(letter)});
    return inputGates.at(letter) ;
}

Gate* TextToGate(string expression){
    if (expression.length() <= 1)
        return getInputInstance(expression);
    else {
        string operation = getGateNameFromText(expression) ;
        string firstMember = getGateFirstMemberFromText(expression);
        if (operation == "negate"){
            return getLogicGate(operation,TextToGate(firstMember),NULL);
        }
        else{
            string secondtMember = getGateSecondMemberFromText(expression);
            return getLogicGate(operation,TextToGate(firstMember),TextToGate(secondtMember));
        }
    }
}

void Simulation(OutputGate gate){
    string cmd ;
    while(true)
    {
        cout << "type 'continue' to end the simulation" << endl ;
        cout << "type 'stop' to end the simulation" << endl ;
        cin >> cmd ;
        if (cmd == "stop")
            break ;
        else{
            gate.simulate() ;
        }

    }
}

void TextToFile(string expression){
    ofstream myfile;
    myfile.open ("example.txt");
    myfile << expression + "\n";
    myfile.close();
}

string FileToText(string filename){
    string line = "";
    ifstream myfile (filename);
    if (myfile.is_open()) {
        getline (myfile,line) ;
        myfile.close();
        return line ;
    }
    else cout << "Umpossible d'ouvrir le fichier"; 
    return line ;
}

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
    string text =  GateToText(A)  ;
    cout << text << endl ;
    cout << GateToText(TextToGate(text)) << endl ; 
    // clear cache of input Instances
    inputGates.clear();

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