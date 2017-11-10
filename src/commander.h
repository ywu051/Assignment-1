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
      

            if (strcmp(conn->str, ";") == 0) {
                return true;
            }              
            else if (conn->exec == exec)
                return true;
            else
                return false;
        }

        void setCS(CmdString cs) {CS = cs;}

        bool execute() {
            unsigned int size = CS.V.size();
            unsigned int count = 0;
            string str;

            pid_t pid, w;
            int status;
            bool run = true;
            bool ex = false;

            do {
                //std::cout << "inside while" << endl;
                //
            
                if ((strcmp(CS.V[count]->str, "exit") == 0 || strcmp(CS.V[count]->str, "Exit") == 0 
                    || strcmp(CS.V[count]->str, " exit") == 0 || strcmp(CS.V[count]->str, " Exit") == 0) && run == true) {
                    ex = true;
                    return true;
                    
                }

                pid = fork();
            
                //cout << "right before pid if statements" << endl;
 
                if (pid > 0) {
                    // parent fork
                    //cout << "parent" << endl;
                    w = wait(&status);
                    //parser for individual commands//
                    if (w == -1) {
                        CS.V[count]->exec = false;
                        //exit(EXIT_FAILURE);
                    }
                    else
                        CS.V[count]->exec = true;

                    if (count < CS.V.size() - 1) {
                        run = runNext(CS.V[count]->exec, CS.V[count+1]);
                       
                    }
                }
                else if (pid == 0) {           // !! It is probably possible to simplify this code by replacing the vector<char*> with the char** already being used

                    //cout << "child - parse" << endl;

                    // must parse Command in CmdString at current position
                    str = CS.V[count]->str;
                    char* ch = new char[str.length()];
                    strcpy(ch, str.c_str());
                    vector<char*> vch;
                    
                    char* tok = strtok(ch, " ");
                    
                    while (tok != NULL) {
                        vch.push_back(tok);
                        tok = strtok(NULL, " ");    
                    }
                    vch.push_back('\0');                 
                    //intending to instantiate array of char pointers
                    int vsize = vch.size();
                    char** charr = new char* [vsize];
                    for (unsigned int j = 0; j < vch.size(); j++) {
                        charr[j] = vch[j];
                    }

                     
                    if (run) {
                      
                        execvp(charr[0], charr);
                        perror(*charr);
                    }
                    else {
                        CS.V[count]->exec = true;
                        run = true;
                    }
                }
                else {
                    std::cout << "fork failed" << std::endl;
                }
                count += 2;
              
            } while (count <= size - 1 && ex == false);
            CS.V.clear();
            if (ex == true) {return true;}
            else
                return false;
        }  

};


#endif // __COMMANDER_H__
