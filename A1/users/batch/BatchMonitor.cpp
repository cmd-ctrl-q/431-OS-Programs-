/*
resources:

https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c#

http://www.cplusplus.com/reference/regex/regex_match/
*/

#include <string>
#include <iostream> 
#include <stdio.h>
#include <dirent.h>
using namespace std; 

// globals 
DIR *dir; 
struct dirent *ent;
char *defaultDir = "jobs/"; // default directory 


unsigned int menuOption() {

    int selection;

    printf("\n0: Quit");
    printf("\n1. List jobs in directory");
    printf("\n2. Run 1 job");
    printf("\n3. Run all jobs");
    printf("\n4. Set jobs directory"); 
    printf("\n5. Help\n");
    printf("\nEnter selection: "); 
    cin >> selection; 

    return selection; 
}

/* helper funcion for checking user input for menu option */
int checkAndRunMenu() {

    bool valid = false; 
    int selection; 

    /* check user input validity */ 
    while(!valid) { 
        selection = menuOption();

        if ((selection >= 0) && (selection <= 5)) {
            valid = true; 
        } else {
            printf("Error: Invalid Selection. \n");
        }
    }
    return selection;
}

void run() {

    bool running, valid; 
    unsigned int selection;
    
    string job, command; 

    running = true; 
    while(running) {

        selection = checkAndRunMenu();

        /* Initiate user option */
        switch(selection) {
            case 0: 
                /* shutdown */
                running = false; 
                break; 
            case 1: 
                /* list jobs in dir */
                command = "ls " + string(defaultDir);
                system(command.c_str());
                printf("\n");
                break; 
            case 2: 
                /* run one job */
                printf("Enter job name: "); 
                cin >> job;

                /* compile job */
                command = "g++ " + string(defaultDir) + job + ".cpp";
                cout << command << endl;
                system(command.c_str());

                /* run job */
                system("./a.out");
                break;
            case 3: 
                /* run all jobs */
                if ((dir = opendir(defaultDir)) != NULL) {
                    /* access files in jobs dir */ 
                    while((ent = readdir (dir)) != NULL) {
                        // if file begins with . then ignore
                        // if(regex_match(string(ent->d_name), std::regex("^\\."))) {
                        //     continue;
                        // }
                        if(string(ent->d_name).length() < 3) {
                            continue; 
                        }
                        printf("\n%s\n", ent->d_name); 

                        /* compile job */ 
                        // command = "g++ jobs/" + string(ent->d_name);
                        command = "g++ " + string(defaultDir) + string(ent->d_name);
                        system(command.c_str());

                        /* run job */ 
                        system("./a.out");
                        printf("\n");
                    }
                    closedir(dir);
                } 
                break; 
            case 4: 
                /* set jobs dir */ 
                printf("Set directory/path for jobs: "); 
                break; 
            case 5:
                /* help */ 
                const char *text =
                "\nUsage:" 
                "\n"
                "The commands are:"
                "\n<option>\t <description>"
                "\n\t0\t shutdown"
                "\n\t1\t list jobs in directory"
                "\n\t2\t run a single job"
                "\n\t\t\t input: <filename>(.cpp)"
                "\n\t3\t run all jobs in directory (change directory with option 4)"
                "\n\t4\t set the job directory (default: /jobs/)"
                "\n\t5\t help\n";
                printf("%s", text);
                break; 
        }
    }
}


int main() {
    
    run();
    
    return 1;
}

