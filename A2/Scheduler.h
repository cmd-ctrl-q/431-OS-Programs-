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

        void switchstate(int opt, int arrival) {

            list <PCB*> :: iterator it; 
            switch(opt)
            {
            case 1: // from new state to ready state
                for(it = this->newstate.begin(); it != this->newstate.end(); ++it) {
                    if((*it)->tArrival == arrival) {
                        this->readystate.push_back(*it);
                        // delete from prev state the process that was transfered 
                        this->newstate.erase(it);
                    }
                }
                break;
            case 2: // from ready state to running state
                // runningstate = this->readystate.front();
                if(this->readystate.size() != 0) {
                    it = this->readystate.begin(); 
                    this->runningstate.push_back(*it);
                    this->readystate.erase(it);
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

        // average response time 
        // void findart(int timeinq, int arrival) {
        //     art += double(timeinq - arrival)/4.0;
        // }

        // // average turnaround time 
        // void findatt(int completiontime, int arrival) {
        //     att += double(completiontime - arrival)/4.0;
        // }

    public:

        // --------- FIELDS --------- 
        int size;                   // number of processes in scheduler
        int currtotalburst;         // current total cpu bursts
        double art;             // average response time 
        double att;             // verage turnaround time
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
            int _arrival = 0;   // i think same thing as total cpu bursts
            int option = 0;
            bool running = true;

            // todo: update pcb properties (eg completion, etc)
            while(running) { 

                // loop through newstate, add processes to readystate
                if(this->newstate.size() != 0) {
                    for(int i = 0; i < newstate.size(); i++) {
                        this->switchstate(1, _arrival);
                    }
                }

                // ready -> run              
                this->switchstate(2, _arrival);

                // loop based on cpu burst for the process in runningstate 
                if(this->runningstate.size() != 0) {
                    _burst = this->runningstate.front()->cpuBurst;
                    // update pcb's initial time in running q
                    this->runningstate.front()->tInitial = currtotalburst; 
                    // find art 
                    // this->findart(currtotalburst, _arrival); // may keep
                    for(int i = 0; i < _burst; i++) {
                        // add some job

                        // try and update ready states
                        if(this->newstate.size() > 0) {
                            this->switchstate(1, ++_arrival);
                        }
                        this->currtotalburst++; 
                    }
                    // update same pcb's completion time out of running q
                    this->runningstate.front()->tCompletion = currtotalburst; 
                    // find att 
                    // findatt(currtotalburst, _arrival);
                    // running->terminated
                    this->switchstate(5, _arrival); 
                } 

                // printf("\n\n newstate");
                // this->printlist(1);
                // printf("\n\n readystate");
                // this->printlist(2);
                // printf("\n\n runningstate");
                // this->printlist(3);
                // printf("\n\n terminatedstate");
                // this->printlist(5);

                // if terminatedstate is empty, all processes are done
                running = this->allterm(); 
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