#ifndef DATA_TYPES_H
#define DATA_TYPES_H

struct FileNode;
struct WordNode;

typedef struct FileNode {
    char *filePath;
    struct WordNode *wordList;
    int word_count;
    struct FileNode *next;
} FileNode;

typedef struct WordNode{
    char *word;
    float freq;
    struct WordNode *next;
} WordNode;

#endif
