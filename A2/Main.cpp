/*
Program a simulation of a job scheduler for an operating system. 
Your scheduler will read in a list of jobs with the relevant 
information and output the order of completion along with the 
time of completion for each job and other relevant statistics.

Implement 3 scheduling that were discussed in class.
a. First Come, First Served (batch, non preemptive)
b. Shortest Job First (batch, non preemptive)
c. Round Robin (preemptive)
*/

#include <iostream>     /* cout */ 
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <string>       /* string type */
#include "Scheduler.h"

using namespace std;

int main() { 

    Scheduler* scheduler = new Scheduler(7); 
    scheduler->makePCB(100, 0, 10); // (pid, arrival time, cpu burst)
    scheduler->makePCB(101, 6, 10); 
    scheduler->makePCB(102, 8, 4);
    scheduler->makePCB(103, 12, 20);
    scheduler->makePCB(104, 19, 15);
    scheduler->makePCB(105, 30, 5);
    scheduler->makePCB(106, 35, 10);

    scheduler->printlist(1);    // print before algo
    scheduler->FCFS();          // run algo
    scheduler->printlist(0);    // print after algo 

    scheduler->printlist(6);    // art 
    scheduler->printlist(7);    // att
}