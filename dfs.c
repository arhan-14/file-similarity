#include <stdio.h>
#include <sys/stat.h>
#include "data_types.h"

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

int *dfs(char **argv){
	char err = 0;
    char *curr = argv
    while(curr != NULL){
        int isDir = check_path(curr);
        if(isDir == -1){
            err = -1
            continue;
        }
        else if(isDir == 0){
            
        }
    }
}
