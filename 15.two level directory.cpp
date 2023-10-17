#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DIRECTORIES 50
#define MAX_FILES_PER_DIRECTORY 50
#define MAX_FILENAME_LENGTH 50
#define MAX_DIRECTORY_NAME_LENGTH 50
struct File {
    char filename[MAX_FILENAME_LENGTH];
    int size;
};
struct Directory {
    char dirname[MAX_DIRECTORY_NAME_LENGTH];
    struct File files[MAX_FILES_PER_DIRECTORY];
    int fileCount;
};
struct TwoLevelDirectory {
    struct Directory directories[MAX_DIRECTORIES];
    int directoryCount;
};
void initializeTwoLevelDirectory(struct TwoLevelDirectory *twodir) {
    twodir->directoryCount = 0;
}
void listFiles(struct TwoLevelDirectory *twodir) {
    if (twodir->directoryCount == 0) {
        printf("No directories in the two-level directory.\n");
        return;
    }
    for (int i = 0; i < twodir->directoryCount; i++) {
        printf("Directory: %s\n", twodir->directories[i].dirname);
        if (twodir->directories[i].fileCount > 0) {
            printf("Files in the directory:\n");
            for (int j = 0; j < twodir->directories[i].fileCount; j++) {
                printf("\t%s (%d bytes)\n", twodir->directories[i].files[j].filename, twodir->directories[i].files[j].size);
            }
        } else {
            printf("\tNo files in this directory.\n");
        }
    }
}
void createDirectory(struct TwoLevelDirectory *twodir, char *dirname) {
    if (twodir->directoryCount >= MAX_DIRECTORIES) {
        printf("Directory limit reached. Cannot create more directories.\n");
        return;
    }
    if (strlen(dirname) > MAX_DIRECTORY_NAME_LENGTH) {
        printf("Directory name is too long. Maximum length is %d characters.\n", MAX_DIRECTORY_NAME_LENGTH);
        return;
    }
    strcpy(twodir->directories[twodir->directoryCount].dirname, dirname);
    twodir->directories[twodir->directoryCount].fileCount = 0;
    twodir->directoryCount++;
    printf("Directory '%s' created.\n", dirname);
}
void createFile(struct TwoLevelDirectory *twodir, char *dirname, char *filename, int size) {
    int dirIndex = -1;
    for (int i = 0; i < twodir->directoryCount; i++) {
        if (strcmp(twodir->directories[i].dirname, dirname) == 0) {
            dirIndex = i;
            break;
        }
    }
    if (dirIndex == -1) {
        printf("Directory '%s' not found in the two-level directory.\n", dirname);
        return;
    }
    struct Directory *directory = &twodir->directories[dirIndex];
    if (directory->fileCount >= MAX_FILES_PER_DIRECTORY) {
        printf("Directory '%s' is full. Cannot create more files in it.\n", dirname);
        return;
    }
    if (strlen(filename) > MAX_FILENAME_LENGTH) {
        printf("Filename is too long. Maximum length is %d characters.\n", MAX_FILENAME_LENGTH);
        return;
    }
    strcpy(directory->files[directory->fileCount].filename, filename);
    directory->files[directory->fileCount].size = size;
    directory->fileCount++;
    printf("File '%s' created with size %d bytes in directory '%s'.\n", filename, size, dirname);
}
void deleteFile(struct TwoLevelDirectory *twodir, char *dirname, char *filename) {
    int dirIndex = -1;
    for (int i = 0; i < twodir->directoryCount; i++) {
        if (strcmp(twodir->directories[i].dirname, dirname) == 0) {
            dirIndex = i;
            break;
        }
    }
    if (dirIndex == -1) {
        printf("Directory '%s' not found in the two-level directory.\n", dirname);
        return;
    }
    struct Directory *directory = &twodir->directories[dirIndex];
    int found = 0;
    for (int i = 0; i < directory->fileCount; i++) {
        if (strcmp(directory->files[i].filename, filename) == 0) {
            found = 1;
            printf("File '%s' deleted from directory '%s'.\n", filename, dirname);
            for (int j = i; j < directory->fileCount - 1; j++) {
                strcpy(directory->files[j].filename, directory->files[j + 1].filename);
                directory->files[j].size = directory->files[j + 1].size;
            }
            directory->fileCount--;
            break;
        }
    }
    if (!found) {
        printf("File '%s' not found in directory '%s'.\n", filename, dirname);
    }
}
int main() {
    struct TwoLevelDirectory twodir;
    initializeTwoLevelDirectory(&twodir);
    int choice;
    char dirname[MAX_DIRECTORY_NAME_LENGTH];
    char filename[MAX_FILENAME_LENGTH];
    int size;
    while (1) {
        printf("\nTwo-Level Directory Management\n");
        printf("1. List Files and Directories\n");
        printf("2. Create Directory\n");
        printf("3. Create File\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                listFiles(&twodir);
                break;
            case 2:
                printf("Enter directory name: ");
                scanf("%s", dirname);
                createDirectory(&twodir, dirname);
                break;
            case 3:
                printf("Enter directory name: ");
                scanf("%s", dirname);
                printf("Enter filename: ");
                scanf("%s", filename);
                printf("Enter file size (in bytes): ");
                scanf("%d", &size);
                createFile(&twodir, dirname, filename, size);
                break;
            case 4:
                printf("Enter directory name: ");
                scanf("%s", dirname);
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                deleteFile(&twodir, dirname, filename);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}