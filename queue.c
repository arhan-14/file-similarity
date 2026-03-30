#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


Queue *init(){
    Queue *q = malloc(sizeof(Queue));
    if(q == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue *q, char *ptr, int fromArg){
    QueueNode *newNode = malloc(sizeof(QueueNode));
    if(newNode == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    newNode->data = ptr;
    newNode->next = NULL;
    newNode->fromArg = fromArg;

    if(q->tail){
        q->tail->next = newNode;
    } else {
        q->head = newNode;
    }

    q->tail = newNode;
    q->size++;
}

QueueNode *dequeue(Queue *q){
    if(q->size == 0){
        return NULL;
    }

    QueueNode *temp = q->head;
    q->head = q->head->next;
    q->size--;

    if(q->size == 0){
        q->tail = NULL;
    }

    temp->next = NULL;
    return temp;
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

