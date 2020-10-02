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

        bool allterm() {
            if(this->terminatedstate.size() != this->size) {
                return !false; // true, continue running scheduler
            } 
            return !true; // false, stop running scheduler
        }

        void showlist(list <PCB*> g) {
            printf("\nProcessID\tArrival\t\tcpuBurst\tPriority\n");
            list <PCB*> :: iterator it; 
            for(it = g.begin(); it != g.end(); ++it) {
                (*it)->printPCB();
                cout << '\n';
            }
        }

        void switchstate(int opt, int arrival) {

            list <PCB*> :: iterator it; 
            switch(opt)
            {
            case 1: // from new state to ready state
                for(it = this->newstate.begin(); it != this->newstate.end(); ++it) {
                    if((*it)->tArrival == arrival) {
                        // cout << "case 1: --found: " << (*it)->pid << endl;
                        this->readystate.push_back(*it);
                        cout << (*it)->pid << " arrived " << (*it)->tArrival << endl;
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
                // it = runningstate.begin();
                // this->waitingstate.push_back(*it);
                // this->runningstate.clear(); // clear entire list 
                break;
            case 4: // from waiting state to ready state
                break;
            case 5: // from running state to terminated state
                // if(this->runningstate.size() != 0) {
                    it = runningstate.begin(); 
                    this->terminatedstate.push_back(*it);
                    this->runningstate.erase(it);
                    this->runningstate.clear();
                // }

                // for(it = this->runningstate.begin(); it != this->runningstate.end(); ++it) {
                    // this->terminatedstate.push_back(*it);
                        // delete from prev state the process that was transfered 
                        // this->runningstate.erase(it);
                // this->terminatedstate.push_back(*it); // push to terminated list
                break;
            default:
                printf("Cant recognize that option");
                break;
            }
        }

    public:

        // --------- FIELDS --------- 
        int size;
        int currtotalburst; // current total cpu bursts
        list <PCB*> newstate;        //1
        list <PCB*> runningstate;    //2
        list <PCB*> readystate;      //3
        list <PCB*> waitingstate;    //4
        list <PCB*> terminatedstate; //5

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
            int eye = 0;
            // loop through ready state and run processes 
            std::string _state = ""; 
            int _burst;  // individual cpu bursts
            int _arrival = 0; // i think same thing as total cpu bursts
            int option = 0;
            bool running = true;

            // todo: update pcb properties (eg completion, etc)
            while(running) { 

                // loop through newstate, add processes to readystate
                if(this->newstate.size() != 0) {
                    for(int i = 0; i < newstate.size(); i++) {
                        this->switchstate(1, _arrival);
                    }
                    printf("\n readystate: ");
                    this->printlist(2);
                    printf("\n");
                }

                // ready -> run              
                this->switchstate(2, _arrival);

                // loop based on cpu burst for the process in runningstate 
                if(this->runningstate.size() != 0) {
                    _burst = this->runningstate.front()->cpuBurst;
                    for(int i = 0; i < _burst; i++) {
                        // add some job

                        // try and update ready states
                        if(this->newstate.size() > 0) {
                            this->switchstate(1, ++_arrival);
                        }
                        this->currtotalburst++; 
                    }
                    // running->terminated
                    this->switchstate(5, _arrival); 
                } 

                printf("\n\n newstate");
                this->printlist(1);
                printf("\n\n readystate");
                this->printlist(2);
                printf("\n\n runningstate");
                this->printlist(3);
                printf("\n\n terminatedstate");
                this->printlist(5);

                // print terminatedstate 
                // this->printlist(5);

                // if terminatedstate is empty, all processes are done
                running = this->allterm(); 
            } 
        }

        void printlist(int i) {

            switch (i)
            {
            case 1:
                showlist(this->newstate);
                break;
            case 2:
                showlist(this->readystate);
                break;
            case 3:
                showlist(this->runningstate);
                break;
            case 4:
                showlist(this->waitingstate);
                break;
            case 5:
                showlist(this->terminatedstate);
                break;
            default:
                cout << "Could not find that list" << endl;
                break;
            }
        }


};

#endif
