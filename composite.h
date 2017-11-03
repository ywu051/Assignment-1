#ifndef __COMPOSITE_H__
#define __COMPOSITE_H__
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Instruction {
    public:
        char* str;
        bool exec;

        Instruction() {exec = false;}
        Instruction(char* s) {str = s;}

        virtual void execute() = 0;
    
        void setString(char* s) {str = s;}

        virtual void print() = 0;
};

class Command : public Instruction {
    public:
        Command() {}
        Command(char* s) : Instruction(s) {};

        void execute() {
            // execute using execvp and vipid //
            /* take boolean value from execvp
               and assign to exec             */

            
        }

        void print() {cout << str << " ";}
};

class Connector : public Instruction {
    public:
        Connector() {}
        Connector(char* s) : Instruction(s) {
            if (s == ";") {exec = true;}
            if (s == "&") {exec = true;}
            if (s == "|") {exec = false;}
        }

        void execute() {}

        void print() {cout << str << " ";}
};

class CmdString : public Instruction {
    public:
        vector<Instruction*> V;

        CmdString() {}

        void addInstruction(Instruction* i) {
            V.push_back(i);
        }

        void execute() {}
        
        void print() {
            for (int i = 0; i < V.size(); i++) {
                V[i]->print();
                cout << endl;
            }
        }
};


#endif // __COMPOSITE_H__
