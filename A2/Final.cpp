#include <iostream> 
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

using namespace std; 


struct Pcb {
    int pid;
    int arrival;
    int burst;
};

Pcb pcbs[7];

int pids[7];
int arrivals[7];
int bursts[7];




// get response time 
void getRespFCFS(int arrivals[], int n, int bursts[], int resps[]) 
{ 
    resps[0] = 0; 
    for (int  i = 1; i < n ; i++) {

        resps[i] = bursts[i-1] + resps[i-1] ; 
    }
} 

// function to find the waiting time for all processes
void getRespSJF(int pids[], int arrivals[], int n, int bursts[], int resps[]) {
    // sort pcbs by burst count (do not sort first pcb) 
    int temp;
    int curr_arrival_time = arrivals[0];
    // int ordered[n];
    // copy(bursts, bursts+n, ordered);
    // bubble sort bursts
    for(int i = 1; i < sizeof &bursts; i++) { 
        for(int j = i+1; j < sizeof &bursts-1; j++) {
            if(bursts[i] > bursts[j]) {

                temp = bursts[i];
                bursts[i] = bursts[j];
                bursts[j] = temp;

                temp = pids[i];
                pids[i] = pids[j];
                pids[j] = temp;

                temp = arrivals[i];
                arrivals[i] = arrivals[j];
                arrivals[j] = temp;
            }
        }
    }
    // set initial wait time
    resps[0] = 0;
 
    // get response time
    for (int i = 1; i < n ; i++) {
        resps[i] = arrivals[1] + resps[i-1];
    }
}

void getRespRobin(int arrivals[], int n, int bursts[], int resps[], int quanta) { 
    // Make a copy of burst times burst_arr[] to store remaining 
    // burst times. 
    int final_arr[n];  
    for (int i = 0 ; i < n ; i++) 
        final_arr[i] =  bursts[i]; 
  
    int t = 0; // Current time 
    bool running = true; 

    // loop through processes until finish
    while(running) { 

        for (int i = 0 ; i < n; i++) { 
            if (final_arr[i] > 0) { 
                running = false; 
  
                if (final_arr[i] > quanta) { 
                    t += quanta; 
  
                    final_arr[i] -= quanta; 
                } else { 
                    t = t + final_arr[i]; 
                    resps[i] = t - resps[i]; 
                    final_arr[i] = 0; 
                } 
            } 
        } 
    } 
} 
  
// Function to calculate turn around time 
void getTaTime(int arrivals[], int n, int bursts[], int resp[], int ta_time[]) { 

    for(int i = 0; i < n; i++) {
        ta_time[i] = bursts[i] + resp[i];
    }
} 
  
//Function to calculate average time 
void findavgTime(int option, int pids[], int arrivals[], int n, int bursts[], int quanta) { 

    int resp[n], ta_time[n], avg_resp_time = 0, avg_ta_time = 0; 
  
    //Function to find waiting time of all processes 

    switch(option) {
        case 1:
            getRespFCFS(arrivals, n, bursts, resp); 
        case 2:
            getRespSJF(pids, arrivals, n, bursts, resp);
        case 3:
            getRespRobin(arrivals, n, bursts, resp, quanta);
    }
   getRespRobin(arrivals, n, bursts, resp, quanta);

    // get ta time
    getTaTime(arrivals, n, bursts, resp, ta_time); 
  
    // print header
    cout << "Process ID\t" << "CPU Burst\t" << "Arrival\t\t" << "Completion\t" << "Initial Entry\n"; 
  
    // get art and att averages
    for (int  i=0; i<n; i++) 
    { 
        avg_resp_time += (resp[i] - arrivals[i]); // avg resposne time
        avg_ta_time += (ta_time[i] - arrivals[i]); // avg t/a time 
        cout << pids[i] << "\t\t" << bursts[i] <<"\t\t" << arrivals[i] << "\t\t" << ta_time[i] <<"\t\t" << resp[i] << endl; 
    } 
  
    // print stats
    cout << "Avg resp time = " << (float)avg_resp_time / (float)n; 
    cout << "\nAvg t/a time= " << (float)avg_ta_time / (float)n; 
} 

void retrieveData(int x, string _file) {


    ifstream infile;
    infile.open(_file); 
    int i = 0; 
    int n = 0;
    string si;

    for(string line; getline(infile, line);) {
        string::size_type sz; 

        Pcb pcb;
        si = "";
        // n = 0;
        i = 0;
        int arr[3];

        stringstream ssin(line); 
        while(ssin.good() && i < 3) {
            ssin >> arr[i]; 
            ++i;
        } 
        for(i = 0; i < 3; i++) {
            switch(i) {
                case 0:
                    pcb.pid = arr[0];
                    pids[n] = arr[0];
                case 1:
                    pcb.arrival = arr[1];
                    arrivals[n] = arr[1];
                case 2:
                    pcb.burst = arr[2];
                    bursts[n] = arr[2];
            }
        }
        // cout << pcb.pid << " " << pcb.arrival << " " << pcb.burst << endl;
        pcbs[n] = pcb;
        n++;
    }
    infile.close();
}

// Driver code 
int main() { 

    int n = 7;
    retrieveData(n, "input.txt");

    cout << "\n\nFCFS" << endl;
    findavgTime(1, pids, arrivals, n, bursts, -1); // 1: FCFS

    cout << "\n\nSJF" << endl;
    findavgTime(2, pids, arrivals, n, bursts, -1); // 2: SJF

    cout << "\n\nRound Robin" << endl;
    findavgTime(3, pids, arrivals, n, bursts, 15);


    return 0; 
} 