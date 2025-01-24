#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/shm.h>
#include "psem.h"
#include "buffer.h"

const int SHMKEY = 1234;
const int SIZE = 100;

buffer *sbuf;

void handler(int sigNum);
char *generateName(int num);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Invalid syntax\n");
    exit(1);
  }

  const int NUM = atoi(argv[1]);

  signal(SIGINT, handler);

  int shmid;
  psem_t mutex1, mutex2;

  if ((shmid = shmget(SHMKEY, sizeof(buffer), 0666 | IPC_CREAT)) == -1) {
    fprintf(stderr, "Failed to execute shmget\n");
    exit(1);
  }

  sbuf = (buffer *)shmat(shmid, NULL, 0);

  if (argc == 3 && getFinish(sbuf)) {
    fprintf(stderr, "All the philosophers have already been seated\n");
    exit(1);
  } else if (argc == 3 && !getFinish(sbuf)) {
    buf_init(sbuf);
    finished(sbuf);
  } else {
    buf_init(sbuf);
  }

  int n1, n2;
  if (argc == 2) {
    n1 = NUM, n2 = NUM+1;
  } else {
    n1 = NUM, n2 = 1;
  }
  if (!psem_init(&mutex1, generateName(n1), 1)) {
    fprintf(stderr, "Failed to initialize semaphore\n");
    exit(1);
  }
  if (!psem_init(&mutex2, generateName(n2), 1)) {
    fprintf(stderr, "Failed to initialize semaphore\n");
    exit(1);
  }

  while (getFlag(sbuf)) {
    printf("Philosopher %d is thinking\n", NUM);

    psem_wait(&mutex1);
    psem_wait(&mutex2);

    printf("Philosopher %d is eating\n", NUM);

    psem_post(&mutex1);
    psem_post(&mutex2);

    sleep(5);
  }

  printf("Exiting program\n");

  psem_destroy(&mutex1);

  return 0;
}

void handler(int sigNum) {
  if (sigNum == SIGINT) {
    changeFlag(sbuf);
    return;
  }
}

char *generateName(int num) {
  char *name = (char *)malloc(SIZE * sizeof(char));
  sprintf(name, "MUTEX %d", num);
  return (char *)name;
}
