#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode{
    char *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue{
    QueueNode *head;
    QueueNode *tail;
    int size;
} Queue;

void enqueue(Queue *q, char *ptr);
char *dequeue(Queue *q);
void free_queue(Queue *q);

#endif