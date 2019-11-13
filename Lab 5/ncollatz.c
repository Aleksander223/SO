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

int main(int argc, char const *argv[]) {

    pid_t pids[argc - 1];
    int i;
    int n = argc - 1;

    // shared memory
    char shm_name[] = "collatz_shm";
    int shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

    if(shm_fd < 0) {
        perror(NULL);
        return errno;
    }

    int size = 4096 * n;

    if (ftruncate(shm_fd, size) == -1) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    char* result = (char*) mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (result == MAP_FAILED) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    int partition_size = 4096;

    for(i = 0; i < n; i++){
        if((pids[i] = fork()) < 0){
            return errno;
        }
        else if(pids[i] == 0){
            //children
            char partsize[16], off[16];
            sprintf(partsize, "%d", partition_size);
            sprintf(off, "%d", i * partition_size);

            char *args[] = {"collatz", (char*) argv[i + 1], partsize, off, NULL};
            execve("/home/aleks/Desktop/SO/Lab 5/collatz", args, NULL);
            perror(NULL);
        }
        else{
            pid_t cpid = wait(NULL);


        }
    }

    for(int j = 0; j < size; j += partition_size) {
        printf("%s\n", result + j);
    }

    shm_unlink(shm_name);

    return 0;
}
