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

int main() {
    char shm_name[] = "test_shm";

    int shm_fd;

    shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

    if(shm_fd < 0) {
        perror(NULL);
        return errno;
    }

    int size = 4096;

    // if (ftruncate(shm_fd, size) == -1) {
    //     perror(NULL);
    //     shm_unlink(shm_name);
    //     return errno;
    // }

    char* p = (char*) mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("%s\n", p);

    munmap(p, size);

    shm_unlink(shm_name);

    return 0;
}
