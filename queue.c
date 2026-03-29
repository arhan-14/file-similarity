#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"


Queue *init(){
    Queue *q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue *q, char *ptr){
    char *newData = strdup(ptr);
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->data = newData;
    newNode->next = NULL;

    if(q->tail){
        q->tail->next = newNode;
    }

    q->tail = newNode;

    if(q->size == 0){
        q->head = newNode;
    }
    q->size += 1;
}

char *dequeue(Queue *q){
    if(q->size == 0){
        return NULL;
    }
    QueueNode *temp = q->head;
    char *result = temp->data;
    if(q->size == 1){
        q->tail = NULL;
    }

    q->head = q->head->next;
    free(temp);
    q->size -= 1;
    return result;
}

void free_queue(Queue *q){
    QueueNode *temp = q->head;
    while(temp){
        QueueNode *next = temp->next;
        free(temp->data);
        free(temp);
        temp = next;
    }
    free(q);
}

