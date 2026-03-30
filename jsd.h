#ifndef JSD_H
#define JSD_H

#include <string.h>
#include "data_types.h"

typedef struct {
    FileNode *file_a;
    FileNode *file_b;
    int combined_word_count;
    float distance;
} Comparison;

float jsd(FileNode *a, FileNode *b);
int analyze(FileNode *fileList);

#endif
