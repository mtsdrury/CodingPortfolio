# Cellular Automata Simulation

This project is a simulation of cellular automata based on a hybrid automata approach. It models the behavior of cells through various states (REST, INCREASING, DECREASING) influenced by differential equations and external parameters.

## Project Components

The simulation is structured into several C source files and headers, each serving a specific role:

- **`main.c`**: Entry point of the program, manages the overall execution flow.
- **`automata_logic.c`**: Core logic for cellular behavior and state updates.
- **`state_transition.c`**: Implements the logic for transitioning between states.
- **`priority_queue.c`**: Priority queue for managing the event-driven simulation.
- **`diffusion.c`**: Manages diffusion effects between cells.
- **`utilities.c`**: Utility functions including reading from input files.
- **Headers**: `config.h`, `automata.h` provide the definitions and constants used across the project.

Each source file is accompanied by a header file defining the functions and constants used.

