#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames, pages[50], n, frame[10], time[10];
    int pageFaults = 0, counter = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page numbers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for (int i = 0; i < frames; i++) {
        frame[i] = -1; // initialize frames as empty
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                counter++;
                time[j] = counter; // update recent time
                break;
            }
        }

        // If not found, it's a page fault
        if (!found) {
            int pos = -1;

            // Look for an empty frame
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, use LRU
            if (pos == -1) {
                pos = findLRU(time, frames);
            }

            frame[pos] = pages[i];
            counter++;
            time[pos] = counter;
            pageFaults++;
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
