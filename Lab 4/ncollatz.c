#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[]) {

    pid_t pids[argc - 1];
    int i;
    int n = argc - 1;

    for(i = 0; i < n; i++){
        if((pids[i] = fork()) < 0){
            return errno;
        }
        else if(pids[i] == 0){
            //children
            char *args[] = {"collatz", (char*) argv[i + 1], NULL};
            execve("/home/aleks/Desktop/SO/Lab 4/collatz", args, NULL);
            perror(NULL);
        }
        else{
            //pid_t cpid = wait(NULL);
        }
    }

    return 0;
}
