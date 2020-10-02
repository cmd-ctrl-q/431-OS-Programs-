#include <iostream> 
#include <stdio.h>
#include <unistd.h> 

int main() {

    // usleep(1000000);
    pid_t pid = fork();
    int x = 1;

    if(pid < 0) {
        printf("child process creation failed\n");
    } else if(pid > 0) {
        // do parent operations
        // x = 0;
        for(int i = 1; i < 50; i++) {
            usleep(1000000);
            printf("%u x%u parent\n", i, x);
            // x++;
        }
    } else {
        // do child operations 
        x = 0;
        for(int i = 1; i < 25; i++) {
            usleep(2000000);
            printf("%u x%u child\n", i, x);
            // x+=2;
        }
    }
    return 0;
}
