#include <stdio.h>
#include <stdlib.h>
#define MEMORY_SIZE 1000
typedef struct MemoryBlock {
    int size;
    int allocated;
} MemoryBlock;
void initializeMemory(MemoryBlock memory[], int size) {
    for (int i = 0; i < size; i++) {
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}
void displayMemory(MemoryBlock memory[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Block %d: Size=%d Allocated=%d\n", i, memory[i].size, memory[i].allocated);
    }
}
int firstFit(MemoryBlock memory[], int size, int requestSize) {
    for (int i = 0; i < size; i++) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = 1;
            return i;
        }
    }
    return -1; 
}
int bestFit(MemoryBlock memory[], int size, int requestSize) {
    int bestFitBlock = -1;
    int bestFitSize = MEMORY_SIZE + 1;
    for (int i = 0; i < size; i++) {
        if (!memory[i].allocated && memory[i].size >= requestSize && memory[i].size < bestFitSize) {
            bestFitBlock = i;
            bestFitSize = memory[i].size;
        }
    }
    if (bestFitBlock != -1) {
        memory[bestFitBlock].allocated = 1;
    }
    return bestFitBlock;
}
int worstFit(MemoryBlock memory[], int size, int requestSize) {
    int worstFitBlock = -1;
    int worstFitSize = -1;
    for (int i = 0; i < size; i++) {
        if (!memory[i].allocated && memory[i].size >= requestSize && memory[i].size > worstFitSize) {
            worstFitBlock = i;
            worstFitSize = memory[i].size;
        }
    }
    if (worstFitBlock != -1) {
        memory[worstFitBlock].allocated = 1;
    }
    return worstFitBlock;
}
int main() {
    MemoryBlock memory[MEMORY_SIZE];
    initializeMemory(memory, MEMORY_SIZE);
    int choice, requestSize, block;
    while (1) {
        printf("\nMemory Allocation Strategies\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 4) {
            break;
        }
        if (choice < 1 || choice > 3) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }
        printf("Enter the size of memory request: ");
        scanf("%d", &requestSize);
        if (requestSize <= 0) {
            printf("Invalid request size. Please try again.\n");
            continue;
        }
        switch (choice) {
            case 1:
                block = firstFit(memory, MEMORY_SIZE, requestSize);
                break;
            case 2:
                block = bestFit(memory, MEMORY_SIZE, requestSize);
                break;
            case 3:
                block = worstFit(memory, MEMORY_SIZE, requestSize);
                break;
        }
        if (block != -1) {
            printf("Memory allocated in Block %d\n", block);
        } else {
            printf("Memory allocation failed. No suitable block found.\n");
        }
        displayMemory(memory, MEMORY_SIZE);
    }
    return 0;
}