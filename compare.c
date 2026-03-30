#include <stdio.h>
#include <stdlib.h>
#include "data_types.h"
#include "findFiles.h"
#include "jsd.h"
 
int main(int argc, char **argv) 
{
    if (argc < 2) 
    {
        fprintf(stderr, "usage: %s file/directory ...\n", argv[0]);
        return EXIT_FAILURE;
    }
 
    int err = 0;
    FileNode *fileList = findFiles(argv + 1, &err);
 
    int result = analyze(fileList);
 
    if (err) result = EXIT_FAILURE;
    return result;
}
