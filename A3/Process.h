#ifndef Process_H
#define Process_H

#include <iostream>

class Process {

    public: 
        int pid; 
        std::string message; 
        Process(int pid, std::string message);

        void PrintProcess();
};

#endif 