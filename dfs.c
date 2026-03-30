#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include "data_types.h"
#include "queue.h"

static int check_path(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        perror(path); 
        return -1;
    }

    if (S_ISREG(path_stat.st_mode)) return 0;
    if (S_ISDIR(path_stat.st_mode)) return 1;
    return -1;  
}

FileNode *dfs(char **argv) {
    FileNode *fileHead = malloc(sizeof(FileNode));
    fileHead->filePath = NULL;
    fileHead->wordList = NULL;
    fileHead->word_count = 0;
    fileHead->next = NULL;

    int err = 0;
    Queue *q = init();

    char **temp = argv;
    while (*temp) {
        enqueue(q, strdup(*temp));
        temp++;
    }

    if (q->size == 0) {
        free(q);
        free(fileHead);
        return NULL;
    }

    FileNode *tempNode = fileHead;
    char *currPath = dequeue(q);

    while (currPath != NULL) {
        int isDir = check_path(currPath);  

        if (isDir == -1) {
            err = -1; 
            free(currPath);
        } else if (isDir == 0) {
            size_t len = strlen(currPath);
            if (len < 4 || strcmp(currPath + len - 4, ".txt") != 0) {
                free(currPath);
            } else {
                FileNode *newNode = malloc(sizeof(FileNode));
                newNode->filePath = currPath;
                newNode->wordList = NULL;
                newNode->word_count = 0;
                newNode->next = NULL;
                tempNode->next = newNode;
                tempNode = newNode;
            }
        } else {
            DIR *dir = opendir(currPath);
            if (dir == NULL) {
                perror(currPath);
                err = -1;
                free(currPath);
            } else {
                struct dirent *entry;
                while ((entry = readdir(dir)) != NULL) {
                    if (strcmp(entry->d_name, ".") == 0 ||
                        strcmp(entry->d_name, "..") == 0)
                        continue;

                    size_t pathLen = strlen(currPath) + strlen(entry->d_name) + 2;
                    char *childPath = malloc(pathLen);
                    snprintf(childPath, pathLen, "%s/%s", currPath, entry->d_name);
                    enqueue(q, childPath);
                }
                closedir(dir);
                free(currPath);
            }
        }

        currPath = dequeue(q); 
    }

    free_queue(q);

    if (err) return NULL;
    return fileHead;
}