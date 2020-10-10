#ifndef Scheduler_H
#define Scheduler_H
#include "PCB.h"
#include <iostream>
#include <list>
#include <iterator>

using namespace std;

// initialize static variables 
int PCB::priority = 1;

/* Scheduler + Algorithms */
class Scheduler {

    private:
        // --------- METHODS ----------
        bool allterm() {
            if(this->terminatedstate.size() != this->size) {
                return !false; // true, continue running scheduler
            } 
            return !true; // false, stop running scheduler
        }

        void showbefore(list <PCB*> g) {
            printf("\nProcessID\tCPU Burst\tArrival\t\tPriority\n");
            list <PCB*> :: iterator it; 
            for(it = g.begin(); it != g.end(); ++it) {
                (*it)->printPCB();
                cout << '\n';
            }
        }

        void showafter(list <PCB*> g) {
            //pid, cpuBurst, tArrival, tCompletion, tInitial
            printf("\nProcessID\tCPU Burst\tArrival\t\tCompletion\tInitial Entry\n");
            list <PCB*> :: iterator it; 
            for(it = g.begin(); it != g.end(); ++it) {
                (*it)->printPCBf();
                cout << '\n';
                // find art and att
                this->art += double(((*it)->tInitial) - ((*it)->tArrival))/double(this->size);
                this->att += double(((*it)->tCompletion) - ((*it)->tArrival))/double(this->size);
            }
        }

        void switchstate(int opt, int arrival, int cpuburst) {

            list <PCB*> :: iterator it; 
            switch(opt)
            {
            case 1: // from new state to ready state
                for(it = this->newstate.begin(); it != this->newstate.end(); ++it) {
                    // FCFS
                    if(arrival != -1) {
                        if((*it)->tArrival == arrival) {
                            this->readystate.push_back(*it);
                            // delete from prev state the process that was transfered 
                            this->newstate.erase(it);
                        }
                    } 

                }
                break;
            case 2: // from ready state to running state
                // runningstate = this->readystate.front();
                if(this->readystate.size() != 0) {
                    // FCFS
                    if(arrival != -1) {
                        it = this->readystate.begin(); 
                        this->runningstate.push_back(*it);
                        this->readystate.erase(it);
                    }
                    // SJF
                    if(cpuburst != -1) {
                        
                        if((*it)->cpuBurst == cpuburst) {
                            this->runningstate.push_back(*it);
                            // delete from prev state the process that was transfered 
                            this->newstate.erase(it);
                        }
                    }
                } 
                break;
            case 3: // from running state to waiting state
                it = runningstate.begin();
                this->waitingstate.push_back(*it);
                this->runningstate.erase(it); // clear entire list 
                break;
            case 4: // from waiting state to ready state                    
                if(true) { // hault running process 
                    it = runningstate.begin(); 
                    this->waitingstate.push_back(*it);
                    this->runningstate.erase(it);
                }
                break;
            case 5: // from running state to terminated state
                    it = runningstate.begin(); 
                    // update art 
                    // this->findart(this->currtotalburst,(*it)->tArrival);
                    // update art
                    this->terminatedstate.push_back(*it);
                    this->runningstate.erase(it);
                    this->runningstate.clear();

                break;
            default:
                printf("Unrecognized option");
                break;
            }
        }

    public:

        // --------- FIELDS --------- 
        int size;                   // number of processes in scheduler
        int currtotalburst;         // current total cpu bursts
        double art;                 // average response time 
        double att;                 // average turnaround time
        list <PCB*> newstate;       //1
        list <PCB*> runningstate;   //2
        list <PCB*> readystate;     //3
        list <PCB*> waitingstate;   //4
        list <PCB*> terminatedstate;//5

        // --------- CONSTRUCTOR ---------
        Scheduler(int size) {
            this->size = size;
        }

        // --------- METHODS ----------
        void makePCB(int pid, int arrival, int burst) {
            PCB* pcb = new PCB(pid, arrival, burst);
            // add to newstate 
            newstate.push_back(pcb);
        }


        // --------- ALGORITHMS ---------
        void FCFS() {
            this->art = 0;
            this->att = 0;
            std::string _state = ""; 
            int _burst;         // individual cpu bursts
            int _arrival = 0; 
            int option = 0;
            bool running = true;

            while(running) { 

                // newstate -> readystate
                if(this->newstate.size() != 0) {
                    for(int i = 0; i < newstate.size(); i++) {
                        this->switchstate(1, _arrival, -1);
                    }
                }
                // ready -> run              
                this->switchstate(2, _arrival, -1);

                if(this->runningstate.size() != 0) {
                    _burst = this->runningstate.front()->cpuBurst;
                    // update pcb's initial time in running q
                    this->runningstate.front()->tInitial = currtotalburst; 
                    for(int i = 0; i < _burst; i++) {
                        // add some job here
                        // try and update ready states
                        if(this->newstate.size() > 0) {
                            this->switchstate(1, ++_arrival, -1);
                        }
                        this->currtotalburst++; 
                    }
                    // update same pcb's completion time out of running q
                    this->runningstate.front()->tCompletion = currtotalburst; 
                    this->switchstate(5, _arrival, -1); 
                } 
                // if terminatedstate is empty, all processes are done
                running = this->allterm(); 
            } 
        }

        void SFJ_NP() {
            this->art = 0;
            this->att = 0;
            std::string _state = ""; 
            int _burst;         // individual cpu bursts
            int _arrival = 0; 
            int option = 0;
            bool running = true;
            list <PCB*> :: iterator it; 

            while(running) {

                // add processes to readystate based on their arrival time
                // newstate -> readystate
                if(this->newstate.size() != 0) {
                    for(int i = 0; i < newstate.size(); i++) { 
                        // add first process to readystate then to runningstate
                        if(i == 0) {
                            this->switchstate(1, _arrival, -1); // to readystate
                            this->switchstate(2, _arrival, -1); // to runningstate
                        } else {
                            this->switchstate(1, _arrival, -1);
                        }
                    }
                }

                // loop through processes in readystate and add to runningstate
                // based on cpuburst and if there is already a process in runningstate
                if(this->readystate.size() != 0) {

                    if(this->runningstate.size() == 0) {
                        // add next shortest burst process from readystate to runningstate
                        it = this->readystate.begin();
                        _burst = (*it)->cpuBurst; 
                        for(it; it != this->readystate.end(); ++it) {
                            if((*it)->cpuBurst < _burst) {
                                _burst = (*it)->cpuBurst;
                            }
                        }
                        // move smallest cpuburst process to runningstate 
                        this->switchstate(2, -1, _burst);
                    } else { // else if size != 0
                        // else increment burst 
                        _burst = this->runningstate.front()->cpuBurst;
                    }
                }
            }
        }


        void printlist(int i) {

            switch (i)
            {
            case 1:
                showbefore(this->newstate);
                break;
            case 2:
                showbefore(this->readystate);
                break;
            case 3:
                showbefore(this->runningstate);
                break;
            case 4:
                showbefore(this->waitingstate);
                break;
            case 5:
                showbefore(this->terminatedstate);
                break;
            case 6:
                cout << "art: " << this->art << endl;
                break;
            case 7:
                cout << "att: " << this->att << endl;
                break;
            case 0: 
                showafter(this->terminatedstate);
                break;
            default:
                cout << "Could not find that list" << endl;
                break;
            }
        }
};

#endif