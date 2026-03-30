#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode{
    char *data;
    int fromArg; 
    struct QueueNode *next;
} QueueNode;

typedef struct Queue{
    QueueNode *head;
    QueueNode *tail;
    int size;
} Queue;

Queue *init();
void enqueue(Queue *q, char *ptr, int fromArg);
QueueNode *dequeue(Queue *q);
void free_queue(Queue *q);

#endif