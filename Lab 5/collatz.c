#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char const *argv[]){
    int counter = 0;

    int n = atoi(argv[1]);
    int size = atoi(argv[2]);
    int offset = atoi(argv[3]);

    // mem
    char shm_name[] = "collatz_shm";
    int shm_fd = shm_open(shm_name, O_RDWR, S_IRUSR|S_IWUSR);

    if(shm_fd < 0) {
        perror(NULL);
        return errno;
    }

    char* result = (char*) mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, offset);

    if (result == MAP_FAILED) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    if(n == 0){
        return 0;
    }

    pid_t pid = fork();

    if(pid < 0){
        return errno;
    }
    else if(pid == 0){
        // child
        sprintf(result, "%d: ", n);
        do{
            sprintf(result + strlen(result), "%d ", n);
            // result[counter++] = n;
            if(n % 2 == 0){
                n /= 2;
            }
            else{
                n = 3*n + 1;
            }
        }while(n != 1);
        // sprintf(result + strlen(result), "\n");
    }
    else{
        //parent
        pid_t cpid = wait(NULL);
        printf("Done Parent %d| Me %d\n", getppid(), cpid);

        munmap(result, size);
    }

    return 0;
}
