#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head) {
    int totalSeekTime = 0;

    printf("\nDisk Movement:\n");
    printf("%d", head);
    for (int i = 0; i < n; i++) {
        printf(" -> %d", requests[i]);
        totalSeekTime += abs(requests[i] - head);  // Calculate absolute difference
        head = requests[i];  // Move head to next request
    }

    printf("\n\nTotal Seek Time = %d\n", totalSeekTime);
}

int main() {
    int n, head, diskSize;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    
    int requests[n];
    printf("Enter the disk request queue: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    // Checking if requests are within disk size
    for (int i = 0; i < n; i++) {
        if (requests[i] >= diskSize) {
            printf("Error: Request %d exceeds disk size %d. Exiting program.\n", requests[i], diskSize);
            return 1;
        }
    }

    if (head >= diskSize) {
        printf("Error: Initial head position exceeds disk size. Exiting program.\n");
        return 1;
    }

    fcfs(requests, n, head);
    return 0;
}
