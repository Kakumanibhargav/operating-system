#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILES 50
#define FILENAME_LENGTH 20
struct File {
    char filename[FILENAME_LENGTH];
    int size;
};
struct Directory {
    struct File files[MAX_FILES];
    int fileCount;
};
void initializeDirectory(struct Directory *dir) {
    dir->fileCount = 0;
}
void listFiles(struct Directory *dir) {
    if (dir->fileCount == 0) {
        printf("No files in the directory.\n");
        return;
    }
    printf("Files in the directory:\n");
    for (int i = 0; i < dir->fileCount; i++) {
        printf("%s (%d bytes)\n", dir->files[i].filename, dir->files[i].size);
    }
}
void createFile(struct Directory *dir, char *filename, int size) {
    if (dir->fileCount >= MAX_FILES) {
        printf("Directory is full. Cannot create more files.\n");
        return;
    }
    if (strlen(filename) > FILENAME_LENGTH) {
        printf("Filename is too long. Maximum length is %d characters.\n", FILENAME_LENGTH);
        return;
    }
    strcpy(dir->files[dir->fileCount].filename, filename);
    dir->files[dir->fileCount].size = size;
    dir->fileCount++;
    printf("File '%s' created with size %d bytes.\n", filename, size);
}
void deleteFile(struct Directory *dir, char *filename) {
    int found = 0;
    for (int i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->files[i].filename, filename) == 0) {
            found = 1;
            printf("File '%s' deleted.\n", filename);
            for (int j = i; j < dir->fileCount - 1; j++) {
                strcpy(dir->files[j].filename, dir->files[j + 1].filename);
                dir->files[j].size = dir->files[j + 1].size;
            }
            dir->fileCount--;
            break;
        }
    }
    if (!found) {
        printf("File '%s' not found in the directory.\n", filename);
    }
}
int main() {
    struct Directory dir;
    initializeDirectory(&dir);
    int choice;
    char filename[FILENAME_LENGTH];
    int size;
    while (1) {
        printf("\nSingle-Level Directory Management\n");
        printf("1. List Files\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                listFiles(&dir);
                break;
            case 2:
                printf("Enter filename: ");
                scanf("%s", filename);
                printf("Enter file size (in bytes): ");
                scanf("%d", &size);
                createFile(&dir, filename, size);
                break;
            case 3:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                deleteFile(&dir, filename);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}