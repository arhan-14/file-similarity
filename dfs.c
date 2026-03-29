#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include "data_types.h"
#include "queue.h"

static char check_path(const char *path){
    struct stat path_stat;
    if(stat(path, &path_stat) != 0){
        perror("%s is not a file/directory");
        return -1;
    }
    
    if (S_ISREG(path_stat.st_mode)) {
        // is a file
        return 0;
    }
    else if(S_ISDIR(path_stat.st_mode)){
        // is a dir
        return 1;
    }
}

void *dfs(char **argv){
    FileNode *fileHead = (FileNode *)malloc(sizeof(FileNode));
    fileHead->filePath = NULL;
    fileHead->wordList = NULL;
    fileHead->next = NULL;

	char err = 0;
    Queue *q = init();

    char *temp = *argv;
    while(temp){
        enqueue(q, temp);
        temp +=1;
    }

    if(q->size == 0){
        free(q);
        return NULL;
    }

    FileNode *tempNode = fileHead;

    char *currPath = dequeue(q);
    while(currPath != NULL){
        
        int isDir = check_path(curr);
        if(isDir == -1){
            err = -1
            continue;
        }
        else if(isDir == 0){
            size_t len = strlen(currPath);
            if(strcmp(currPath + len - 4), ".txt" != 0 || strcmp(currPath,".") == 0){
                free(currPath);
                curr = dequeue(q);
                continue;
            }

            FileNode *newNode = malloc(sizeof(FileNode));
            newNode->filePath = curr;
            newNode->wordList = NULL;
            newNode->next = NULL;
            tempNode = newNode;
        }
        else{
            
        }

        curr = dequeue(q);
    }

    free_queue(q)
}
