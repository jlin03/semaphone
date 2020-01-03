#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define KEY 123123

union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };


int main(int argc,char * argv[]) {
  int semaphore;
  int memory;
  union semun su;
  struct sembuf sb;

  su.val = 1;
  sb.sem_num = 0;
  sb.sem_op = -1;

  if(argc == 2) {
    if(strcmp(argv[1],"-c") == 0) {
      semaphore = semget(KEY,1,IPC_CREAT|0644);
      memory = shmget(KEY,1024,IPC_CREAT|0644);
      semctl(semaphore,0,SETVAL,su);
      FILE * f = fopen("stuff","w");
      fclose(f);
      printf("semaphore created\n");
      printf("shared memory created\n");
      printf("file created\n");
    }
    if(strcmp(argv[1],"-r") == 0) {
      semaphore = semget(KEY,1,0);
      memory = shmget(KEY,1024,0);
      semop(semaphore,&sb,1);

      FILE * f = fopen("stuff","r");
      char temp[1024];
      while(fgets(temp,1024,f)) {
        printf("%s",temp);
      }

      semctl(semaphore,IPC_RMID,0);
      semctl(memory,IPC_RMID,0);
      remove("stuff");

      printf("semaphore removed\n");
      printf("shared memory removed\n");
      printf("file removed\n");

    }
    if(strcmp(argv[1],"-v") == 0) {
      FILE * f = fopen("stuff","r");
      char temp[1024];
      while(fgets(temp,1024,f)) {
        printf("%s",temp);
      }
    }
  }



}
