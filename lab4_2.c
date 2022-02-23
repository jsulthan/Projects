#include <stdio.h>       /* for fprintf() */
#include <stdlib.h>      /* for exit() */
#include <unistd.h>      /* for sleep() */
#include <pthread.h>     /* for pthreads functions */

#define NTHREADS 2

int string_index = 0;

char string_to_print[] = "0123456789";

pthread_mutex_t lock;

void *func(void *arg)
{
    pthread_mutex_lock(&lock);
   int tmp_index;

   sleep(1);   /* sleep 1 sec to allow all threads to start */

   while (1) {
      tmp_index = string_index;

      if ((tmp_index = 0)) {
         printf("B%c ", string_to_print[tmp_index]);
         usleep(1);   /* sleep 1 usec */
        string_index = tmp_index + 1;
      }
      if ((tmp_index = 1)) {
         printf("A%c ", string_to_print[tmp_index]);
         printf("A%c ", string_to_print[tmp_index+1]);
         usleep(1);   /* sleep 1 usec */
        string_index = tmp_index + 2;
      }
      if ((tmp_index = 3)) {
         printf("B%c ", string_to_print[tmp_index]);
         printf("B%c ", string_to_print[tmp_index+1]);
         usleep(1);   /* sleep 1 usec */
          string_index = tmp_index + 2;
      }
      if ((tmp_index = 5)) {
         printf("A%c ", string_to_print[tmp_index]);
         printf("A%c ", string_to_print[tmp_index+1]);
         usleep(1);   /* sleep 1 usec */
         string_index = tmp_index + 2;
      }
      if ((tmp_index = 7)) {
         printf("B%c ", string_to_print[tmp_index]);
         printf("B%c ", string_to_print[tmp_index+1]);
         usleep(1);   /* sleep 1 usec */
         string_index = tmp_index + 2;
      }
      if ((tmp_index = 9)) {
         printf("A%c \n", string_to_print[tmp_index]);
         usleep(1);   /* sleep 1 usec */
         string_index = 0;
      }
   }
}


int main(void)
{
   pthread_t threads[NTHREADS];
   int k;

   for (k = 0; k < NTHREADS; k++) {
      printf("Starting Thread %d\n", k+1);
      if (pthread_create(&threads[k], NULL, &func, NULL) != 0) {
            printf("Error creating thread %d\n", k+1);
            exit(-1);
      }
   }

   sleep(20);   /* sleep 20 secs to allow time for the threads to run */
                /* before terminating them with pthread_cancel()      */

   for (k = 0; k < NTHREADS; k++) {
      pthread_cancel(threads[k]);
   }

   pthread_exit(NULL);
}
