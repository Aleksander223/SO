#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

int A[256][256];
int B[256][256];
int C[256][256];


typedef struct {
    int i;
    int j;
    int n;
} elem;

void* compute_ij(void* v) {
    elem* tmp = (elem*) v;

    int x = tmp->i;
    int y = tmp->j;

    int sum = 0;

    for(int i = 0; i < tmp->n; i++) {
        sum += A[x][i] * B[i][y];
    }

    C[x][y] = sum;

    free(v);

    return NULL;
}

int main(int argc, char const *argv[]) {
    // A
    int m, n, p;

    scanf("%d %d %d", &m, &n, &p);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // B

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    int num_threads = m * p;
    pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * num_threads);

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < p; j++) {
            elem* element = (elem*) malloc(sizeof(elem));
            element->i = i;
            element->j = j;
            element->n = n;

            if(pthread_create(&threads[i * m + j * p], NULL, compute_ij, element)) {
                perror(NULL);
                return errno;
            }
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < p; j++) {
            void* result;

            if(pthread_join(threads[i * m + j * p], &result)) {
                continue;
            }
        }
    }

    for(int i = 0; i < m; i++) {
        printf("%d. ", i);
        for(int j = 0; j < p; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // for(int i = 0 ; i < m; i++) {
    //     for(int j = 0; j < n; j++) {
    //         printf("%d ", A[i][j]);
    //     }
    //     printf("\n");
    // }


    return 0;
}
