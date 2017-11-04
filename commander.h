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
            if (strcmp(conn->str, ";"))
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

            do {
                //std::cout << "inside while" << endl;

                run = true;
                pid = fork();
            
                //cout << "right before pid if statements" << endl;
 
                if (pid > 0) {
                    // parent fork
                    //cout << "parent" << endl;
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

                    //cout << "child - parse" << endl;

                    // must parse Command in CmdString at current position
                    str = CS.V[count]->str;
                    str = str+"\0";
                    char* ch = new char[str.length()+1];
                    strcpy(ch, str.c_str());
                    vector<char*> vch;
                    
                    char* tok =  strtok(ch, " ");
                    
                    int k = 0;
                    while (tok != NULL) {
                        vch.push_back(tok);
                        tok = strtok(NULL, " ");
                        
                    }   
                    //vch.push_back('\0');   
                    //intending to instantiate array of char pointers//
                    int vsize = vch.size();
                    char** charr = new char* [vsize+1];
                    for (int j = 0; j < vch.size(); j++) {
                        charr[j] = vch[j];
                    }
                    charr[vch.size()] = NULL;
                    //charr[vch.size()] = new char('\0');
                    /*
                    for (int i = 0; i < vsize; i++) {
                        cout << "charr[" << i << "]: " << charr[i] << endl;

                    }
                    */
                    if (run) {
                        cout << execvp(charr[0], charr) << endl;
                        perror(*charr);
                    }
                    else {
                        CS.V[count]->exec = true;
                    }
                }
                else {
                    std::cout << "fork failed" << std::endl;
                }
                count += 2;
            } while (CS.V[count]->str != "exit" && count < size - 1);
        }  
};


#endif // __COMMANDER_H__
