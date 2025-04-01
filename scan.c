#include <stdio.h>
#include <stdlib.h>

void scan(int requests[], int n, int head, int diskSize, int direction) {
    int totalSeekTime = 0;
    int sorted[n + 2], index = 0;

    // Adding head position and boundary (0 or diskSize-1) based on direction
    sorted[index++] = head;
    if (direction == 0) sorted[index++] = 0;
    else sorted[index++] = diskSize - 1;

    // Copy and sort requests
    for (int i = 0; i < n; i++)
        sorted[index++] = requests[i];

    // Sorting requests including head and boundary
    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    // Find the starting position of the head in sorted array
    int pos;
    for (pos = 0; pos < index; pos++) {
        if (sorted[pos] == head) break;
    }

    printf("\nDisk Movement:\n");
    printf("%d", head);

    // Move in the chosen direction first
    if (direction == 1) { // Moving right
        for (int i = pos + 1; i < index; i++) {
            printf(" -> %d", sorted[i]);
            totalSeekTime += abs(sorted[i] - head);
            head = sorted[i];
        }
        for (int i = pos - 1; i >= 0; i--) {
            printf(" -> %d", sorted[i]);
            totalSeekTime += abs(sorted[i] - head);
            head = sorted[i];
        }
    } else { // Moving left
        for (int i = pos - 1; i >= 0; i--) {
            printf(" -> %d", sorted[i]);
            totalSeekTime += abs(sorted[i] - head);
            head = sorted[i];
        }
        for (int i = pos + 1; i < index; i++) {
            printf(" -> %d", sorted[i]);
            totalSeekTime += abs(sorted[i] - head);
            head = sorted[i];
        }
    }

    printf("\n\nTotal Seek Time = %d\n", totalSeekTime);
}

int main() {
    int n, head, diskSize, direction;

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

    printf("Enter scan direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    scan(requests, n, head, diskSize, direction);
    return 0;
}
