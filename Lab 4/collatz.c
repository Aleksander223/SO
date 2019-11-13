#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[]){
    int n = atoi(argv[1]);

    if(n == 0){
        return 0;
    }

    pid_t pid = fork();

    if(pid < 0){
        return errno;
    }
    else if(pid == 0){
        // child
        printf("%d: ", n);
        do{
            printf("%d ", n);
            if(n % 2 == 0){
                n /= 2;
            }
            else{
                n = 3*n + 1;
            }
        }while(n != 1);
        printf("\n");
    }
    else{
        //parent
        //pid_t cpid = wait(NULL);
        //printf("Parent %d| Process %d | Child %d finished\n", getppid(), getpid(), cpid);
    }

    return 0;
}
