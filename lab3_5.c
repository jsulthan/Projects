#include <stdio.h>
#include <math.h>
#include <sys/mman.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>


#define NTHREADS 3
#define SIZE 1000000

struct thread_info {
int col, row;
int a[18][16];
int b[16][18];
int c[18][18];
};

typedef struct thread_info thread_info_t;

void *compute_C_ij(void *arg) {
    int i, j, k, sum;
    thread_info_t *info;
    int a[18][16];
    int b[16][18];
    int c[18][18];
   
    info = (thread_info_t *)arg;

    i = info->row;
    j = info->col;

    sum = 0;
    for (k = 0; k<16; k++){
        sum = sum + (a[i][k]*b[k][j]);
    }
    c[i][j] = sum;
    pthread_exit(NULL);
}

int main(void) {

    int i, j;
    int k=0;
    int a[18][16];
    int b[16][18];
    int c[18][18];

    pthread_t thread[324];
    thread_info_t info[324];
    
    for (i=0; i<18; i++){
        for(j=0; j<16; j++){
            a[i][j] = i+1+j+1;
    }
}

    for(i=0; i<16; i++){
        for(j=0; j<18; j++){
            b[i][j] = i+1+(2*(j+1));
    }
}
 
    k=0;    
    for (i = 0; i<18; i++) {         
        for (j = 0; j<18; j++) {
             info[k].row = i; 
             info[k].col = j;
             if (pthread_create(&thread[k], NULL, &compute_C_ij, (void *)&info[k]) != 0) {                
             printf("Error %d\n", k);
              }       
         pthread_join(thread[k], NULL);
        }
    }

    printf("The Matrix multiplication a * b is: \n");
    for(i=0; i<18; i++){
        for(j=0; j<18; j++){
            printf("%d\t", c[i][j]);
    }
    printf("\n");
    }

    printf("The Diagonal of matrix multiplication a * b is: \n");
        for(i=0; i<18; i++){
            printf("%d \t", c[i][i]);       
    }
    
    for(i=0; i<324; i++){
        pthread_join(thread[k], NULL);
    }
    pthread_exit(NULL);
}
