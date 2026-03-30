#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include "data_types.h"
#include "queue.h"
#include "readFile.h"

#define SUFFIX ".txt"
#define SUFFIX_LEN 4

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

static FileNode *newFileNode() {
    FileNode *node = malloc(sizeof(FileNode));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->filePath = NULL;
    node->wordList = NULL;
    node->word_count = 0;
    node->next = NULL;
    return node;
}

static int hasSuffix(const char *name) {
    size_t len = strlen(name);
    return len >= SUFFIX_LEN && strcmp(name + len - SUFFIX_LEN, SUFFIX) == 0;
}

static int isHiddenName(const char *path) {
    const char *base = strrchr(path, '/');
    base = (base == NULL) ? path : base + 1;
    return base[0] == '.';
}


FileNode *findFiles(char **argv, int *err) {
    if (err) *err = 0; 

    FileNode *fileHead = newFileNode(); 

    Queue *q = init();
    if (!q) { perror("init"); exit(EXIT_FAILURE); }

    for (char **arg = argv; *arg; arg++) {
        if (isHiddenName(*arg)) continue;

        char *copy = malloc(strlen(*arg) + 1);
        if (copy == NULL) {
            perror("malloc");
            exit(1);
        }
        strcpy(copy, *arg);
        if (!copy) { perror("copy"); exit(EXIT_FAILURE); }

        enqueue(q, copy, 1);
    }

    if (q->size == 0) {
        free_queue(q);
        free(fileHead);
        return NULL;
    }

    FileNode *tail = fileHead;
    QueueNode *curr = dequeue(q);

    while (curr != NULL) {
        char *currPath = curr->data;
        int fromArg  = curr->fromArg;
        free(curr);

        int isDir = check_path(currPath);

        if (isDir == -1) {
            if (err) *err = -1;
            free(currPath);

        } else if (isDir == 0) {
            if (fromArg || hasSuffix(currPath)) {
                FileNode *node = newFileNode();
                node->filePath = currPath;
                readFile(node);
                tail->next = node;
                tail = node;
            } else {
                free(currPath);
            }

        } else {
            DIR *dir = opendir(currPath);
            if (dir == NULL) {
                perror(currPath);
                if (err) *err = -1;
            } else {
                struct dirent *entry;
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_name[0] == '.') continue;

                    size_t len = strlen(currPath) + strlen(entry->d_name) + 2;
                    char *childPath = malloc(len);
                    if (!childPath) { perror("malloc"); exit(EXIT_FAILURE); }
                    snprintf(childPath, len, "%s/%s", currPath, entry->d_name);

                    enqueue(q, childPath, 0);
                }
                closedir(dir);
            }
            free(currPath);
        }

        curr = dequeue(q);
    }

    free_queue(q);

    FileNode *result = fileHead->next;
    free(fileHead);
    return result;
}
