#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_KEY 1234
#define BUFFER_SIZE 5  // Queue size

typedef struct {
    int buffer[BUFFER_SIZE]; // Circular queue
    int front, rear;  // Queue pointers
    int count; // Number of items in queue
} SharedMemory;

int main() {
    // Create shared memory
    int shmid = shmget(SHM_KEY, sizeof(SharedMemory), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory
    SharedMemory *shm = (SharedMemory *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Initialize queue
    shm->front = 0;
    shm->rear = 0;
    shm->count = 0;

    // Create child process (Consumer)
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent (Producer)
        for (int i = 1; i <= 10; i++) {
            while (shm->count == BUFFER_SIZE); // Wait if queue is full

            // Insert item into circular queue
            shm->buffer[shm->rear] = i;
            printf("Producer produced: %d\n", i);
            shm->rear = (shm->rear + 1) % BUFFER_SIZE; // Move rear pointer
            shm->count++; // Increase item count
            sleep(1);
        }
    } else {  // Child (Consumer)
        for (int i = 1; i <= 10; i++) {
            while (shm->count == 0); // Wait if queue is empty

            // Remove item from circular queue
            int item = shm->buffer[shm->front];
            printf("Consumer consumed: %d\n", item);
            shm->front = (shm->front + 1) % BUFFER_SIZE; // Move front pointer
            shm->count--; // Decrease item count
            sleep(2);
        }
    }

    // Detach shared memory
    shmdt(shm);

    if (pid > 0) {
        wait(NULL); // Parent waits for consumer to finish
        shmctl(shmid, IPC_RMID, NULL); // Remove shared memory
    }

    return 0;
}
