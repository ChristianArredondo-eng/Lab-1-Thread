#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

pthread_t tid[2];
int ret1, ret2;


static void* child(void *arg){
   unsigned long i = 0;
   pthread_t id = pthread_self();

   for(i=0; i<(0xFFFFFFFF);i++);
   
   if(pthread_equal(id,tid[i])){
    sleep(3);
    printf("\n main thread proccessing done in 3 second\n");
    ret1 = 100;
    pthread_cancel(tid[0]); //after pressing enter the first thread exits
   }
   //1. The child thread in the beginning is sleeping for 3 seconds and then once the process completes the tasl moves to the main method where the main thread is waiting for 3 seconds it is starting the computation.
   sleep(5);
   printf("\n Second thread processing done in 5 second\n");
   pthread_exit(&id);

   return NULL;
}

int main(void){
   int code;
   int *ptr[2];
   pthread_t child_thread;
   code = pthread_create(&(child_thread), NULL, &child, NULL);
   if(code!=0)
      printf(stderr, "pthread_create failed with code:[%s]",strerror(code));

      //2. No the main thread isn't killing the sleeping thread. The print messages are only after the sleep 5 is passed so it completes its goal after the 5 sleeps. Once its completing the 2 steps it continues with the steps: 3, 4, 5
      sleep(5);
      printf("Sleeping done thread created successfully\n");

      printf("\n first thread return value is [%d]\n", *ptr[0]); //value for the first thread
      printf("\n second thread return value is [%d]\n", *ptr[1]); //value for the second thread
      return 0;
}