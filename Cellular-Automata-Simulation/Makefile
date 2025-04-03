CC = gcc
CFLAGS = -Wall -Wextra -g -O2
LIBS = -lm
TARGET = automaton
SRCS = automata.c priority_queue.c
OBJS = automata.o priority_queue.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
