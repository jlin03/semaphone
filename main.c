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

int main() {
  char temp[1024];
  char * temp2;
  int semaphore = semget(KEY,1,0);
  int memory = shmget(KEY,1024,0);

  struct sembuf sb;

  sb.sem_num = 0;
  sb.sem_op = -1;

  semop(semaphore,&sb,1);


  temp2 = shmat(memory,0,0);
  printf("Last addition: %s\n",temp);
  printf("Your addition: ");
  fgets(temp,1024,stdin);
  printf("%s",temp);

  int fd = open("stuff",O_WRONLY|O_APPEND);
  write(fd,temp,strlen(temp));

  strtok(temp,"\n");

  sb.sem_op = 1;
  semop(semaphore,&sb,1);
  shmdt(temp2);



}
