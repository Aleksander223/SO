#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if(pid < 0)
        return errno;
    else if(pid == 0){
        // child
        printf("Parent: %d | Child: %d\n", getppid(), getpid());
        char *argv[] = {"ls", NULL};
        execve("/usr/bin/ls", argv, NULL);
        perror(NULL);
    }
    else{
        // parent
        pid_t cpid = wait(NULL);
        printf("Child #%d finished\n", cpid);
    }
    return 0;
}
