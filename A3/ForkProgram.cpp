/*
Looking at page 12 of your short note set, 
write a fork program in which the parent process writes 
a message at a 1 second interval, and the child process 
writes a different message a 2 second interval.  
Let the parent write 50 messages, and the child 25.  
Design, code, screenshots.  Due September 28.
*/

#include <string>       // string 
#include <stdio.h>      // printf, etc
#include <iostream>     // cout, etc 
#include <time.h>       // time 
#include "Process.h"

Process::Process(int pid, std::string message) {
    this->pid = pid; 
    this->message = message; 
}

void Process::PrintProcess() {
    std::cout << "pid: " << pid << std::endl;
    std::cout << "message: " << message << std::endl;
}

// sleep
void Sleep(double time) { 

    int start = clock();
    double t; 

    do {
        t = (clock()-start)/(double)(CLOCKS_PER_SEC);
    } while (t < time);
}

int main() {

    Process* child = new Process(1, "message from child process");
    Process* parent = new Process(2, "message from parent process");

    int i = 0;

    while (parent->pid != 0 && child->pid != 0) {

        Sleep(1.0);
        i++; 

        // pointless to add if(j>=25) since both processes stop on same iteration
        if (i >= 50) { 
            parent->pid = 0;
            child->pid = 0;
        } 

        // print parent 
        std::cout << i << "s " << parent->message << std::endl;

        // print child
        if (float(i%2) == 0.0) {
            std::cout << i << "s " << child->message << std::endl;
        }
    }
    return 0; 
}
