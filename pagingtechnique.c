#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int main() {
    int mem_size, page_size, no_of_frames, no_of_processes;
    int process_size[MAX], no_of_pages[MAX], page_table[MAX][MAX];

    printf("Enter total memory size: ");
    scanf("%d", &mem_size);

    printf("Enter page/frame size: ");
    scanf("%d", &page_size);

    no_of_frames = mem_size / page_size;

    printf("Enter number of processes: ");
    scanf("%d", &no_of_processes);

    for (int i = 0; i < no_of_processes; i++) {
        printf("\nEnter size of process %d: ", i);
        scanf("%d", &process_size[i]);

        no_of_pages[i] = process_size[i] / page_size;
        if (process_size[i] % page_size != 0)
            no_of_pages[i]++;

        printf("Enter page table for process %d\n", i);
        printf("(Enter -1 if the page is not in memory)\n");

        for (int j = 0; j < no_of_pages[i]; j++) {
            printf("Page %d -> Frame: ", j);
            scanf("%d", &page_table[i][j]);
        }
    }

    int choice;
    do {
        int pid, logical_address;
        printf("\nEnter process ID (0 to %d): ", no_of_processes - 1);
        scanf("%d", &pid);

        if (pid < 0 || pid >= no_of_processes) {
            printf("Invalid Process ID!\n");
        } else {
            printf("Enter logical address: ");
            scanf("%d", &logical_address);

            int page_number = logical_address / page_size;
            int offset = logical_address % page_size;

            if (page_number >= no_of_pages[pid]) {
                printf("Invalid logical address! Page number exceeds.\n");
            } else {
                int frame_number = page_table[pid][page_number];

                if (frame_number == -1) {
                    printf("Page fault! Page %d of process %d is not in memory.\n", page_number, pid);
                } else {
                    int physical_address = frame_number * page_size + offset;
                    printf("Physical Address = %d\n", physical_address);
                }
            }
        }

        printf("\nDo you want to translate another address? (1 for Yes / 0 for No): ");
        scanf("%d", &choice);

    } while (choice == 1);

    return 0;
}
