#ifndef __COMMANDER_H__
#define __COMMANDER_H__
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
#include "composite.h"

class Commander {
    public:
        CmdString CS;

        bool runNext(bool exec, Instruction* conn) {
            if (conn->str == ";")
                return true;
            else if (conn->exec == exec)
                return true;
            else
                return false;
        }

        void setCS(CmdString cs) {CS = cs;}

        void execute() {
            int size = CS.V.size();
            int count = 0;
            string str;

            pid_t pid, w;
            int status;
            bool run = true;            

            while (CS.V[count]->str != "exit" && count < size - 1) {
                //std::cout << "inside while" << endl;

                run = true;
                pid = fork();
            
                cout << "right before pid if statements" << endl;
 
                if (pid > 0) {
                    // parent fork
                    w = wait(&status);
                    //parser for individual commands//
                    if (w == -1) {
                        CS.V[count]->exec = false;
                        exit(EXIT_FAILURE);
                    }
                    else
                        CS.V[count]->exec = true;
                    if (CS.V.size() - 1 != count) {
                        run = runNext(CS.V[count]->exec, CS.V[count+1]);
                    }
                }
                else if (pid == 0) {

                    cout << "child - parse" << endl;

                    // must parse Command in CmdString at current position
                    str = CS.V[count]->str;
                    char* ch = new char[str.length()];
                    strcpy(ch, str.c_str());
                    vector<char*> vch;

                    char* tok =  strtok(ch, " ");
                    cout << tok << endl;
                    while (tok != NULL) {
                        //cout << "tok: " << tok << endl;
                        vch.push_back(tok);
                        tok = strtok(NULL, " ");
                    }                    
                    //intending to instantiate array of char pointers//
                    int vsize = vch.size() + 1;
                    char** charr = new char* [vsize];
                    for (int j = 0; j < vch.size(); j++) {
                        cout << "vch[j]: " << vch[j] << endl;
                        charr[j] = vch[j];
                        cout << "charr[j]: " << charr[j] << endl;
                    }
                    charr[vch.size()] = new char('\0');
                    
                    for (int i = 0; i < vsize; i++) {
                        cout << "charr[" << i << "]: " << charr[i] << endl;
                    }

                    if (run) {
                        cout << "finish him" << endl; 
                        execvp(charr[0], charr);
                    }
                    else {
                        CS.V[count]->exec = true;
                    }
                }
                else {
                    std::cout << "fork failed" << std::endl;
                }
                count += 2;
            }
        } 

        
        
};


#endif // __COMMANDER_H__
