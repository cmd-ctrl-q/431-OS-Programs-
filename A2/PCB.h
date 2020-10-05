#ifndef PCB_H
#define PCB_H 

#include <iostream>

class PCB {

    public: 
        // --------- PROPERTIES ---------
        int pid;
        static int priority;
        int tCompletion;    // completion time
        int tInitial;       // initial entry 
        std::string state;
        std::string job;

        int cpuBurst;       // cpu burst time 
        int tArrival;       // arrival time
        
        // --------- CONSTRUCTORS ---------
        PCB(int pid, int arrival, int burst) {
            // this->pid = rand() % 999999 + 100000;   // create pid
            this->pid = pid;
            this->state = "New";
            this->tArrival = arrival;
            this->cpuBurst = burst;
        }
        PCB() {};

        // --------- METHODS ---------
        // update arrival time property
        void setarrival(int startTime, int endTime) {
            this->tArrival = (endTime - startTime);
        }

        // update completion time property
        void setcompletion(int startTime, int endTime) {
            this->tCompletion = (endTime - startTime);
        }

        void setstate(std::string state) {
            this->state = state; 
        }

        // get PCB data
        PCB* getPCB() {
            return this;
        }


        void printPCB() {
            printf("%u\t\t%u\t\t%u\t\t%u", pid, cpuBurst, tArrival, priority);
        }

        void printPCBf() {
            printf("%u\t\t%u\t\t%u\t\t%u\t\t%u", pid, cpuBurst, tArrival, tCompletion, tInitial);
        }
};

#endif 