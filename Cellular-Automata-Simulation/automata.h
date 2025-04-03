#ifndef AUTOMATA_H
#define AUTOMATA_H

//declare PriorityQueue struct 
typedef struct PriorityQueue PriorityQueue;

//define Cell 
typedef struct {
    int state;
    double value;
    double last_transition_time;
} Cell;

//function declarations to be defined in automata.c
void init_grid(const char *filename, Cell ***grid, int *size);
void update_state(Cell **grid, int size, double delta_t, double diffusion_coeff, PriorityQueue *pq, double V_t, double a_incr, double a_decr, int step);
void schedule_transition(Cell **grid, PriorityQueue *pq, int row, int col, double d_t, double value, double a_incr, int step);
void process_transitions(Cell **grid, int size, PriorityQueue *pq, double d_t, double a_decr, int step);
void print_grid(Cell **grid, int size);
double calc_diffusion(Cell **old_grid, int size, int row, int col, double d_t, double a_incr, double a_decr, int step);
double get_updated_voltage(Cell old_grid, double a_incr, double a_decr, int step, double d_t);
double calc_trans_time(double value, double threshold, double a_coeff);

#endif 
