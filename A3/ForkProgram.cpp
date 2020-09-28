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

    int i, j = 1;
    bool running = true;

    while (running) {

        Sleep(1.0);

        if ((i >= 50) || (j >= 25)) { // parent done 
            running = false;
        } 

        // print parent 
        std::cout << i << ". " << parent->message << std::endl;
        i++;

        // print child
        if (i%2 == 0) {
            std::cout << i << ". " << child->message << std::endl;
            j++;
        }
    }


    return 0; 
}
