#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
int produced_count = 0, consumed_count = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    while (produced_count < SIZE) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        int item = produced_count + 1;  // Produce 1 to 5
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % SIZE;
        produced_count++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    while (consumed_count < SIZE) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % SIZE;
        consumed_count++;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
