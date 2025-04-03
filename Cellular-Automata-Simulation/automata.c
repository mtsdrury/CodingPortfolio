#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "priority_queue.h"
#include "automata.h"

//main function
int main(int argc, char **argv) {
	//ensure proper number of command-line arguments
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <input_file> <final_time> <a_incr> <a_decr>\n", argv[0]);
        return EXIT_FAILURE;
    }

	//read in command-line arguments
    const char *input_file = argv[1]; //file name
    double final_time = atof(argv[2]); //final time
	//coefficients
    double a_incr = atof(argv[3]);
    double a_decr = atof(argv[4]); 
    
	//initialize parameters
    double d_t =  0.2;
	double diffusion_coeff = 0.5;
	double curr_time = 0.0;
	double V_t = 0.2;
	double V_p = 1.0;
	double V_r = 0.001;
	int num_steps = (int)ceil(final_time / d_t); //derive num steps from d_t and final time

    int size;
    Cell **grid;
    init_grid(input_file, &grid, &size); //initialize grid with input file

    PriorityQueue *pq = create_pq(); //create priority queue to manage state transitions
    init_pq(grid, size, pq, a_incr, a_decr);   

	//iterate over time steps
    for (int step = 0; step < num_steps; step++) {
        update_state(grid, size, d_t, diffusion_coeff, pq, V_t, a_incr, a_decr, step);
        process_transitions(grid, size, pq, d_t, a_decr, step);
    }

    print_grid(grid, size); //print final grid
	
	//free memory allocated for grid
	for (int i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);
    destroy_pq(pq); //free memory for priority queue

    return 0;
}

/**
 * Initializes the grid with values from the input file
 *
 * Inputs: 'filename' name of input file, 'grid' pointer to the 2d grid of Cells, 
 * 
 * Returns: void, reads 1d size of grid from input file and assigns to 'size'
 */
void init_grid(const char *filename, Cell ***grid, int *size) {
    FILE* infile = fopen(filename, "r"); //open file
	
	//if unable to open file
    if (infile == NULL) {
        printf("Could not open file");
        exit(1);
    }

	//read in first row of file
    fscanf(infile, "%d", size); //assign value to size
    int N = *size; //assign N to dereferenced size

	//allocate memory for grid
    *grid = malloc(N * sizeof(Cell *));
    for (int i = 0; i < N; i++) {
        (*grid)[i] = malloc(N * sizeof(Cell));
    }
    

	//initialize state and value for each cell from input file
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
			//read in int for state and double for value
            fscanf(infile, "%d %lf", &(*grid)[i][j].state, &(*grid)[i][j].value);
            (*grid)[i][j].last_transition_time = 0.0; //set last transition time to 0

        }
    }

    fclose(infile); //close the file
}

/**
 * Update rest cells by calling function to calculate diffusion, calculating the new value of the
 * rest cell, if it has crossed the threshold V_t, transition cell to 'increasing' and schedule a 
 * transition to the decreasing state
 *
 * Inputs: 'grid' 2d grid of cells, 'size' 1d size of grid, 'd_t' step size, 'diffusion_coeff' 
 * diffusion coefficient, 'pq' priority queue to store transition events, 'V_t' threshold for rest
 * cells to transition to increasing, 'a_incr' rate of increase, 'a_decr' rate of decrease,
 * 'step' current step of loop iteration
 * 
 * Returns: void
 */
 void update_state(Cell **grid, int size, double d_t, double diffusion_coeff, PriorityQueue *pq, double V_t, double a_incr, double a_decr, int step) {
	//allocate memory for a temporary grid to hold previous states, values, and 
	//transition times of cells
	Cell **old_grid = malloc(size * sizeof(Cell *));
	
	//copy grid cells over into a temp grid of cells
    for (int i = 0; i < size; i++) {
        old_grid[i] = malloc(size * sizeof(Cell));
        for (int j = 0; j < size; j++) {
            old_grid[i][j].value = grid[i][j].value;  //copy value
            old_grid[i][j].state = grid[i][j].state;  //copy state
            old_grid[i][j].last_transition_time = grid[i][j].last_transition_time; //copy last trans time
        }
    }
    
	//for each cell in original grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
			//if the cell is at rest
            if (grid[i][j].state == 0) {
				//calculate diffusion term
                double diffusion_term = calc_diffusion(old_grid, size, i, j, d_t, a_incr, a_decr, step);
                double new_val = old_grid[i][j].value + d_t * diffusion_coeff * diffusion_term; //calculate the new value

				//if the new cell value has crossed the threshold
                if (new_val > V_t) {
                    grid[i][j].state = 1;  //change the cell's state to increasing
                    schedule_transition(grid, pq, i, j, d_t, V_t, a_incr, step); //schedule its transition to decreasing
                    grid[i][j].value = new_val; //set its value to be the calculated new value
                    grid[i][j].last_transition_time = (step + 1) * d_t ; //set transition time to be next time step
                } else {  //if cell's value did not cross threshold
                    grid[i][j].value = new_val; //only adjust cell's value
                }
            }
        }
    }

	//free memory allocated for old_grid
    for (int i = 0; i < size; i++) {
        free(old_grid[i]);
    }
    free(old_grid);

}

/**
 * Function to schedule the transition of an increasing state cell to the decreasing state
 *
 * Inputs: 'grid' 2d grid of cells, 'pq' priority queue to store transition events, 
 * 'row' row of cell to transition, 'col' column of cell to transition, 'd_t' step size,
 * 'value' value of cell, 'a_incr' rate of increase, 'step' current step of loop iteration
 * 
 * Returns: void
 */
void schedule_transition(Cell **grid, PriorityQueue *pq, int row, int col, double d_t, double value, double a_incr, int step) {
	double V_p = 1.0; //threshold value for increasing->decreasing
	
	//check that values are not negative before taking log
	if (value <= 0 || a_incr <= 0) {
        fprintf(stderr, "Invalid inputs to schedule_transition: value=%.6f, a_incr=%.6f\n", value, a_incr);
        exit(1);
    }
	
	double time_to_decr = (step + 1) * d_t + (log( V_p / value ) / a_incr)  ; //time until state change
    if (time_to_decr > (step + 1) * d_t) {  //make sure it is time in future
        Event event = {row, col, time_to_decr}; //create an event
        pq_push(pq, event); //push event onto the queue
    }
}

/**
 * Function to process the transitions in the priority queue scheduled for any timestep before the next
 *
 * Inputs: 'grid' 2d grid of cells, 'size' 1d size of grid, 'pq' priority queue to store transition events, 
 * 'd_t' step size, 'value' value of cell, 'step' current step of loop iteration
 * 
 * Returns: void
 */
void process_transitions(Cell **grid, int size, PriorityQueue *pq, double d_t, double a_decr, int step) {
    double V_r = 0.001; //threshold to reach the rest state
    double V_p = 1.0;   //threshold to reach the decreasing state
    double next_time = (step + 1) * d_t; //next time step

	//while there are events in the priority queue that are before or at the next time step
    while (!pq_empty(pq) && pq_peek(pq).event_time <= next_time) {
        Event event = pq_pop(pq);  		//remove the event from the priority queue
        int row = event.row;			//store row index
        int col = event.col;			//store column index
        Cell *cell = &grid[row][col];	//access cell corresponding to event

		//if the cell's state was increasing
		if (cell->state == 1) {
			cell->state = 2;	//change it to decreasing
			cell->value =  V_p;	//set value to threshold V_p
			cell->last_transition_time =  next_time; //set transition time as one step in the future

			//solving the analytical solution to the partial differential
			double ratio =  V_r / V_p ;
			double log_val = log(ratio);
			double trans_time_offset = log_val / a_decr; 		//time offset before next transition
			
			double time_to_rest = next_time + trans_time_offset; //time until cell transitions to rest
			Event next_event = {row, col, time_to_rest};		 //create an event for transition to rest
			pq_push(pq, next_event);	//push event onto queue
		} else if (cell->state == 2) {	//if cell was in decreasing state
			cell->state = 0;	//change state to rest
			cell->value = V_r;	//set value to be threshold V_r
			cell->last_transition_time = next_time;	//set transition time to next time step
		}
    }
}

/**
 * Function to get an updated voltage value for cells in increasing and decreasing states
 *
 * Inputs: 'old_cell' cell from temporary grid used to store old properties of cells,
 * 'a_incr' rate of increase, 'a_decr' rate of decrease, 'step' current step of loop iteration, 
 * 'd_t' step size
 * 
 * Returns: the updated voltage of cell
 */
double get_updated_voltage(Cell old_cell, double a_incr, double a_decr, int step, double d_t) {
    double t_last = old_cell.last_transition_time;	
    double elapsed_t = (step * d_t) - t_last;   //compute time elapsed from cell's last transition

	//if cell's state is increasing
    if (old_cell.state == 1) {
        return old_cell.value * exp(a_incr * elapsed_t);	//solve for voltage at current time
    } else if (old_cell.state == 2) {	//if cell is decreasing
        return old_cell.value * exp(a_decr * elapsed_t);	//solve for voltage at current time
    }
	return old_cell.value;
}

/**
 * Function to determine how to get the updated voltage depending on the cell's last state
 *
 * Inputs: 'old_grid' temporary grid used to store old properties of grid cells, 'r' row of cell in grid,
 * 'c' column of cell in grid, 'a_incr' rate of increase, 'a_decr' rate of decrease, 
 * 'step' current step of loop iteration, 'd_t' step size
 * 
 * Returns: the updated voltage of cell, directly if cell is at rest, from helper function otherwise
 */
double get_neighbor_value(Cell **old_grid, int r, int c, double a_incr, double a_decr, int step, double d_t) {
    if (old_grid[r][c].state == 0) {	//if the cell's last state was rest
        return old_grid[r][c].value;	//return its last value
    } else {	//otherwise,
        return get_updated_voltage(old_grid[r][c], a_incr, a_decr, step, d_t);  //return the updated voltage
    }
}


/**
 * Function to calculate the diffusion term from the voltage of all four neigboring cells and the 
 * current cell's last voltage
 *
 * Inputs: 'old_grid' temporary grid used to store old properties of grid cells, 'size' 1d size of grid,
 * 'row' row of cell to calculate diffusion for, 'col' of cell to calculate diffusion for,
 * 'd_t' step size, 'a_incr' rate of increase, 'a_decr' rate of decrease, 'step' current step of loop iteration
 * 
 * Returns: diffusion term for cell at index (row, col)
 */
double calc_diffusion(Cell **old_grid, int size, int row, int col, double d_t, double a_incr, double a_decr, int step) {
    double diffusion_term = 0.0; //initialize diffusion_term

	//if there is an up neighbor
    if (row > 0) {
        diffusion_term += get_neighbor_value(old_grid, row - 1, col, a_incr, a_decr, step, d_t); //get voltage of up neighbor
    } else {	//if first row
        diffusion_term += get_neighbor_value(old_grid, row + 1, col, a_incr, a_decr, step, d_t); //treat down neighbor as up neighbor
    }

	//if there is a down neighbor
    if (row < size - 1) {
        diffusion_term += get_neighbor_value(old_grid, row + 1, col, a_incr, a_decr, step, d_t); //get voltage of down neighbor
    } else {	//if last row
        diffusion_term += get_neighbor_value(old_grid, row - 1, col, a_incr, a_decr, step, d_t); //treat up neighbor as down neighbor
    }

	//if there is a left neighbor
    if (col > 0) {
        diffusion_term += get_neighbor_value(old_grid, row, col - 1, a_incr, a_decr, step, d_t); //get voltage of left neighbor
    } else { 	//if left column
        diffusion_term += get_neighbor_value(old_grid, row, col + 1, a_incr, a_decr, step, d_t); //treat right neighbor as left neighbor
    }

	//if there is a right neighbor
    if (col < size - 1) {
        diffusion_term += get_neighbor_value(old_grid, row, col + 1, a_incr, a_decr, step, d_t); //get voltage of right neighbor
    } else {	//if last column
        diffusion_term += get_neighbor_value(old_grid, row, col - 1, a_incr, a_decr, step, d_t); //treat left neighbor as right neighbor
    }
    
	//current cell's contribution to diffusion term
    diffusion_term -= 4.0 * old_grid[row][col].value;

    return diffusion_term; //return diffusion term
}

/**
 * Function to calculate the amount of time until the next transition, called to initialize the priority queue
 *
 * Inputs: 'curr_val' current value of cell, 'threshold' value to cross for transition to next state,
 * 'a_coeff' rate of diffusion depending on state of cell
 * 
 * Returns: time to the cell's next transition
 */
double calc_trans_time(double curr_val, double threshold, double a_coeff) {
	//ensure no log of negative numbers
	if (curr_val <= 0 || a_coeff == 0 || threshold <= 0) {
		fprintf(stderr, "Cannot calculate transition time.\n");
		exit(1);
	}
	
	return log(threshold / curr_val ) / a_coeff; //return calculation for time to next transition
}

/**
 * Function to print the final states of the grid
 *
 * Inputs: 'grid' 2d grid of cells, 'size' 1d size of grid
 * 
 * Returns: void
 */
void print_grid(Cell **grid, int size) {
	//print top border
	printf("+-");
	for (int i = 0; i < size; i++) {
		printf("--");
	}
	printf("+\n");
	
	//print grid rows
	for (int i = 0; i < size; i++) {
		printf("| "); 	//left border
		for (int j = 0; j < size; j++) {
			if (grid[i][j].state == 1) {
				printf("x "); 	//increasing
			} else if (grid[i][j].state == 2) {
				printf("o "); 	//decreasing
			} else {
				printf("  "); 	//rest
			}
		}
		printf("|\n");	//right border
	}
	
	//print bottom border
	printf("+"); 
	for (int i = 0; i < size; i++) {
		printf("--");
	}
	printf("-+\n");
}
