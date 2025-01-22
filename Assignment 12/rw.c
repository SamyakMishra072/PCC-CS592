#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t rw_mutex = PTHREAD_MUTEX_INITIALIZER; // Ensures mutual exclusion for writers
pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER; // Protects `read_count`
int read_count = 0; // Tracks the number of active readers

// Simulate reading
void *reader(void *arg) {
    int id = *(int *)arg;

    pthread_mutex_lock(&read_mutex); // Lock to update `read_count`
    read_count++;
    if (read_count == 1)
        pthread_mutex_lock(&rw_mutex); // First reader locks writers
    pthread_mutex_unlock(&read_mutex); // Unlock after updating

    printf("Reader %d is reading\n", id);
    sleep(1); // Simulate reading time

    pthread_mutex_lock(&read_mutex); // Lock to update `read_count`
    read_count--;
    if (read_count == 0)
        pthread_mutex_unlock(&rw_mutex); // Last reader unlocks writers
    pthread_mutex_unlock(&read_mutex); // Unlock after updating

    return NULL;
}

// Simulate writing
void *writer(void *arg) {
    int id = *(int *)arg;

    pthread_mutex_lock(&rw_mutex); // Lock to ensure exclusive writing
    printf("Writer %d is writing\n", id);
    sleep(2); // Simulate writing time
    pthread_mutex_unlock(&rw_mutex); // Unlock after writing

    return NULL;
}

int main() {
    int num_readers, num_writers;

    // Get user input for the number of readers and writers
    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);

    pthread_t r_threads[num_readers], w_threads[num_writers];
    int r_ids[num_readers], w_ids[num_writers];

    // Assign IDs to readers and writers
    for (int i = 0; i < num_readers; i++) r_ids[i] = i + 1;
    for (int i = 0; i < num_writers; i++) w_ids[i] = i + 1;

    // Create reader threads
    for (int i = 0; i < num_readers; i++) {
        pthread_create(&r_threads[i], NULL, reader, &r_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < num_writers; i++) {
        pthread_create(&w_threads[i], NULL, writer, &w_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < num_readers; i++) {
        pthread_join(r_threads[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(w_threads[i], NULL);
    }

    return 0;
}