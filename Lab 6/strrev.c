#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

// void* hello(void* v) {
//     char* who = (char*) v;
//     printf("Hello %s!\n", who);
//     return NULL;
// }

void* rev(void* v) {
    char* original = (char*) v;
    int n = strlen(original);
    char* result = (char*) malloc(sizeof(char) * n);

    for(int i = 0; i < n; i++) {
        result[i] = original[n - i - 1];
    }

    result[n] = '\0';

    return result;
}

int main(int argc, char const* argv[]) {
    pthread_t thr;

    // if(pthread_create(&thr, NULL, hello, "world")) {
    //     perror(NULL);
    //     return errno;
    // }
    //
    // void* result;
    //
    // if(pthread_join(thr, &result)) {
    //     perror(NULL);
    //     return errno;
    // }

    char* original;
    strcpy(original, argv[1]);

    if(pthread_create(&thr, NULL, rev, original)) {
        perror(NULL);
        return errno;
    }

    void* result;

    if(pthread_join(thr, &result)) {
        perror(NULL);
        return errno;
    }

    printf("Reverse is: %s\n", (char*) result);

    return 0;
}
