#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

/**
 * Function to create an instance of a PriorityQueue linked list and allocate space for it
 * 
 * Returns: the instance of PriorityQueue 
 */
PriorityQueue* create_pq() {
    PriorityQueue* pq = malloc(sizeof(PriorityQueue));
    if (!pq) {
        fprintf(stderr, "Failed to allocate memory for priority queue.\n");
        exit(EXIT_FAILURE);
    }
    pq->head = NULL; // Start with an empty list
    return pq;
}

/**
 * Function to initialize the priority queue by pushing events onto the queue based on cells
 * initialized in the grid
 *
 * Inputs: 'grid' 2d grid of cells, 'size' 1d size of grid, 'pq' instance of PriorityQueue holding
 * scheduled transitions, 'a_incr' rate of increase, 'a_decr' rate of decrease
 * 
 * Returns: void
 */
void init_pq(Cell **grid, int size, PriorityQueue* pq, double a_incr, double a_decr) {
    double V_r = 0.001, V_p = 1.0; //initialize thresholds to set cell values
    
	//loop through all elements in the grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
			
            if (grid[i][j].state == 1) { //if cell in increasing state
				//calculate time to cell's transition to decreasing
                double time_to_decr = calc_trans_time(grid[i][j].value, V_p, a_incr); 
                Event event = {i, j, time_to_decr}; //create an event
                pq_push(pq, event); //add the event to the queue
            } else if (grid[i][j].state == 2) { //if cell in decreasing state
				//calculate time to cell's transition to decreasing
                double time_to_rest = calc_trans_time(grid[i][j].value, V_r, a_decr);
                Event event = {i, j, time_to_rest}; //create an event
                pq_push(pq, event); // Add the event to the linked list-based PQ
            }
        }
    }
}

/**
 * Function to push an event onto the queue
 *
 * Inputs: 'pq' instance of PriorityQueue holding scheduled transitions, 
 * 'event' instance of Event to be pushed onto the queue
 * 
 * Returns: void
 */
void pq_push(PriorityQueue* pq, Event event) {
    EventNode* new_node = malloc(sizeof(EventNode));	//allocate memory for event node
	
	//if unable to allocate the memory
    if (!new_node) {
        fprintf(stderr, "Failed to allocate memory for event node.\n");
        exit(EXIT_FAILURE);
    }
	
    new_node->event = event; //new_node's event attribute is event
    new_node->next = NULL; 	//new node's next attribute is NULL

    //insert in sorted order
    if (!pq->head || pq->head->event.event_time > event.event_time) {
        //insert at the head
        new_node->next = pq->head;
        pq->head = new_node;
    } else {
        //traverse the list to find the insertion point
        EventNode* current = pq->head; //start at head
        while (current->next && current->next->event.event_time <= event.event_time) {
            current = current->next;
        }
        new_node->next = current->next; //insert new node after current
        current->next = new_node;		//update current to point to new
    }
}

/**
 * Function to pop an event off of the queue from the beginning of the list
 *
 * Inputs: 'pq' instance of PriorityQueue holding scheduled transitions
 * 
 * Returns: Event instance removed from the queue
 */
Event pq_pop(PriorityQueue* pq) {
	//if the queue is empty,
    if (!pq->head) {
        fprintf(stderr, "Priority queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    //remove the head node and save event
    EventNode* temp = pq->head;
    Event min_event = temp->event;
    pq->head = pq->head->next; //move head to next node in queue
    free(temp);
    return min_event;	//return event from removed node
}

/**
 * Function to peek at the next event in the queue
 *
 * Inputs: 'pq' instance of PriorityQueue holding scheduled transitions
 * 
 * Returns: Event instance removed from the queue
 */
Event pq_peek(PriorityQueue* pq) {
	//if queue is empty
    if (!pq->head) {
        fprintf(stderr, "Priority queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    return pq->head->event; //return event stored in head node
}

/**
 * Function to find out whether a priority queue is empty
 *
 * Inputs: 'pq' instance of PriorityQueue holding scheduled transitions
 * 
 * Returns: int representing a boolean
 */
int pq_empty(PriorityQueue* pq) {
    return pq->head == NULL;
}

/**
 * Function to free all memory allocated for an instance of PriorityQueue
 *
 * Inputs: 'pq' instance of PriorityQueue holding scheduled transitions
 * 
 * Returns: void
 */
void destroy_pq(PriorityQueue* pq) {
    EventNode* current = pq->head;	//start at head
	
	//while there are nodes left in list
    while (current) {
        EventNode* temp = current; //store current
        current = current->next;	//make current point to next
        free(temp);	//free node memory
    }
    free(pq); //free priority queue
}


