#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define BUF_SIZE 4096

void assert_fileopen(int f_src){
    if(f_src < 0){
        if(errno == 2){
            printf("Error: file does not exist\n");
        }
        else if(errno == 13){
            printf("Error: file requires permission\n");
        }
        else{
            printf("Error #%d\n", errno);
        }
        exit(errno);
    }
}

int main(int argc, char* argv[]) {
    int f_src = open(argv[1], O_RDONLY);
    int f_dest = open(argv[2], O_WRONLY | O_CREAT);

    assert_fileopen(f_src);
    assert_fileopen(f_dest);

    void* buf = (void*) malloc(BUF_SIZE);

    int r;

    do {
        r = read(f_src, buf, BUF_SIZE);

        if(r < 0){
            printf("Error #%d\n", errno);
            exit(errno);
        }

        write(f_dest, buf, r);
    }while(r);

    close(f_src);
    close(f_dest);

    return 0;
}
