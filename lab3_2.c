#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_info {
    double a, b;
    char op;
   int maxitr;
    int count;
    double c;
   double exec_time;
};

typedef struct thread_info thread_info_t;

void *func(void *arg)
{
   struct timespec time_1, time_2;
   double exec_time;
   thread_info_t *info;
   int i, maxitr, count;
   volatile double a, b, c;

   info = (thread_info_t *)arg;
   maxitr = info->maxitr;
    count = info->count;

   b = 2.3; a = 4.5;

   exec_time = 0.0;

   clock_gettime(CLOCK_REALTIME, &time_1);

    if (count == 1){
        for (i = 0; i < maxitr; i++) {
            c = a + b;
        }
        count = 2;
    }
    else if (count == 2){
        for (i = 0; i < maxitr; i++) {
            c = a - b;
        }
        count = 3;
    }
    else if (count == 3){
        for (i = 0; i < maxitr; i++) {
            c = a * b;
        }
        count = 4;
    }
    else if (count == 4){
        for (i = 0; i < maxitr; i++) {
            c = a / b;
        }
    }
    else{
        printf("Failure \n");
    }

    printf("Computation: %lf\n", c);
   clock_gettime(CLOCK_REALTIME, &time_2);

   exec_time = (time_2.tv_sec - time_1.tv_sec);
   exec_time = exec_time + (time_2.tv_nsec - time_1.tv_nsec)/1.0e9;

   info->exec_time = exec_time;

   pthread_exit(NULL);
   
}

int main(void)
{
   pthread_t thread1;
   thread_info_t info1;
   double maxitr, i, count;

   maxitr = 5.0e8;

   info1.maxitr = (int)maxitr;

    for(i=0; i<4; i++){
    count = i + 1;
    info1.count = (int)count;
   if (pthread_create(&thread1, NULL, &func, &info1) != 0) {
           printf("Error in creating thread 1\n");
           exit(1);
   }

   pthread_join(thread1, NULL);
   printf("Exec time for thread1 = %lf sec\n", info1.exec_time);
}

   pthread_exit(NULL);
}
