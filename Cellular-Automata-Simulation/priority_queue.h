#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "automata.h"

//define Event 
typedef struct {
	int row;
	int col;			//cell index of event
	double event_time;  //time of event
	struct Event *next; //pointer to next event
} Event;

//define EventNode
typedef struct EventNode {
    Event event;
    struct EventNode* next; //pointer to next
} EventNode;

//define PriorityQueue
typedef struct PriorityQueue {
    EventNode* head; 
} PriorityQueue;

//function declarations for PriorityQueue implementation, defined in priority_queue.c
PriorityQueue* create_pq();
void init_pq(Cell **grid, int size, PriorityQueue* pq, double a_incr, double a_decr);
void destroy_pq(PriorityQueue* pq);
void pq_push(PriorityQueue* pq, Event event);
Event pq_pop(PriorityQueue* pq);
Event pq_peek(PriorityQueue* pq);
int pq_empty(PriorityQueue* pq);

#endif
