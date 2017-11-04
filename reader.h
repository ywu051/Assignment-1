#ifndef __READER_H__
#define __READER_H__
#include <iostream>
#include <string>
#include <cstring>
#include "composite.h"

using namespace std;

class Reader {
    public:
        string userInput;
        
        char* tok2;
        char* tok1;

        CmdString CS;

        Reader() {}
        ~Reader() {
            delete tok2;
            delete tok1;

            tok2 = NULL;
            tok1 = NULL;
        }
     
        

        Command* createCommand(char* str) {
            // create Command //
            Command* cmd = new Command();
            cmd->setString(str);
            return cmd;
        };

        Connector* createConnector(char* str) {
            // create Connector //
            return new Connector(str);
        };
    

        // reads input, parses input, calls create function //
        void read() {
            // Use strspn in order to find any '#' character //
            // and remove it and everything after it //
            getline(cin, userInput);

            int finder;
            int finder2;

            char ch = '#';
            char* p = &ch;
            finder = strcspn(userInput.c_str(), p);
            finder2 = strcspn(userInput.c_str(), "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ./");

            userInput = userInput.substr(finder2,finder);

            // converts the substring into two c_str pointers //
            char* ch1 = new char[userInput.size()];
            strcpy(ch1, userInput.c_str());
     
            char* ch2 = new char [userInput.size()];
            strcpy(ch2, userInput.c_str());
            //cout << "3" << endl;
    

            // takes two c_str pointers and takes relevant characters //
            tok2 = strtok(ch2, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-<>./\"");
            tok1 = strtok(ch1, ";&|");

            while (tok1 != NULL) {
                Command* cmd = createCommand(tok1);
                CS.addInstruction(cmd);
           
                if (tok2 != NULL) {
                    CS.addInstruction(createConnector(tok2));
                }

                tok1 = strtok(NULL, ";&|");
                tok2 = strtok(NULL, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-<>./\"");
            }    

        }
      
        // displays command line entry //
        void display() {
            cout << "$ ";
            read();
        } 
};

#endif // __READER_H__
