#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 5 // Number of philosophers

pthread_mutex_t forks[N]; // Mutexes representing forks
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for synchronization

void *philosopher(void *arg) {
    int id = *(int *)arg;

    while (1) {
        // Thinking
        printf("Philosopher %d is Thinking\n", id);
        sleep(1);

        // Picking up forks
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&forks[id]);
        pthread_mutex_lock(&forks[(id + 1) % N]);
        pthread_mutex_unlock(&mutex);

        // Eating
        printf("Philosopher %d is Eating\n", id);
        sleep(2);

        // Putting down forks
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % N]);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i + 1;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
