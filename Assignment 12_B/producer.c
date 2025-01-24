
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "buffer.h"
#include "psem.h"

#define  SHMKEY		1234
#define  DELAY		1000000	  // Micro-seconds
#define  MAXITERATION	30

int
main (void)
{
  int shmid, smem_size, i;
  unsigned x = 0;
  buffer *sbuf = NULL;
  psem_t mutex;
  psem_t empty, full;

  smem_size = sizeof (buffer);
  shmid = shmget (SHMKEY, smem_size, 0666 | IPC_CREAT);		// Allocating space for shared memory
  if (shmid == -1)
    {
      perror ("shmget");
      return 1;
    }

  sbuf = (buffer *) shmat (shmid, NULL, 0);		// Attaching the shared memory space to the local space, to be used as buffer
  buf_init (sbuf);								// Initialising the Buffer space before use
  if (!psem_init (&mutex, "MUTEX", 1))
    return 2;
  if (!psem_init (&empty, "EMPTY", BUFFSIZE))
    return 2;
  if (!psem_init (&full, "FULL", 0))
    return 2;

  i = MAXITERATION;				// Maximum number of iterations the production will continue
  while (i--)
    {
      psem_wait(&empty);
      psem_wait (&mutex);
      x++;
      if (buf_insert (sbuf, x))
	  printf ("\nProduced => %d\n", x);
      else
	  {
	     x--;
	     puts ("Buffer FULL\n");
	  }
      buf_display (sbuf);
      psem_post (&mutex);
      psem_post(&full);
      usleep (DELAY);
    }

  /* Waiting for the Consumer to finish before termination*/
  psem_holdon(&full);
  return 0;
}
