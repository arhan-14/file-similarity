#ifndef DFS_H
#define DFS_H

struct fileNode{
    char *filePath;
    struct wordNode *wordList;
    struct fileNode *next;
};

struct wordNode{
    char *word;
    float freq;
    struct wordNode *next;
};

#endif