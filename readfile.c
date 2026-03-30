#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include "data_types.h"
#include "readFile.h"

#define BUF_SIZE 4096

static WordNode *insertWord(WordNode *head, const char *word) {
    WordNode *cur = head;
    WordNode *prev = NULL;

    while (cur != NULL) {
        int cmp = strcmp(cur->word, word);
        if (cmp == 0) {
            cur->freq += 1.0f;
            return head;
        }
        if (cmp > 0) break;
        prev = cur;
        cur = cur->next;
    }

    WordNode *newNode = malloc(sizeof(WordNode));
    if (!newNode) { perror("malloc"); exit(EXIT_FAILURE); }
    newNode->word = strdup(word);
    if (!newNode->word) { perror("strdup"); exit(EXIT_FAILURE); }
    newNode->freq = 1.0f;
    newNode->next = cur;

    if (prev) prev->next = newNode;
    else head = newNode;

    return head;
}

void readFile(FileNode *node) {
    int fd = open(node->filePath, O_RDONLY);
    if (fd < 0) {
        perror(node->filePath);
        return;
    }

    WordNode *head = NULL;
    int total = 0;

    char buf[BUF_SIZE];
    char *word = NULL;
    int wlen = 0;
    int wcap = 0;
    ssize_t n;

    while ((n = read(fd, buf, BUF_SIZE)) > 0) {
        for (ssize_t i = 0; i < n; i++) {
            char c = buf[i];
            if (isalpha((unsigned char)c) || isdigit((unsigned char)c) || c == '-') {
                if (wlen + 1 >= wcap) {
                    wcap = wcap == 0 ? 16 : wcap * 2;
                    word = realloc(word, wcap);
                    if (!word) { perror("realloc"); exit(EXIT_FAILURE); }
                }
                word[wlen++] = tolower((unsigned char)c);
            } else {
                if (wlen > 0) {
                    word[wlen] = '\0';
                    head = insertWord(head, word);
                    total++;
                    wlen = 0;
                }
            }
        }
    }

    if (wlen > 0) {
        word[wlen] = '\0';
        head = insertWord(head, word);
        total++;
    }

    free(word);
    close(fd);

    if (total > 0) {
        WordNode *cur = head;
        while (cur != NULL) {
            cur->freq /= (float)total;
            cur = cur->next;
        }
    }

    node->wordList = head;
    node->word_count = total;
}
