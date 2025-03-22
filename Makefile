CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L
SRCS = src/main.c src/query_interface.c
OBJS = $(SRCS:.c=.o)
TARGET = program



all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET) -f example.csv
/*
CFLAGS = -Wall -Wextra -g  # Enable warnings & debugging
LIBS = -lm  # Link against the math library

Object files
OBJ = main.o data_structures.o

Compile .c files into .o files
%.o: %.c
    $(CC) -c -o $@ $< $(CFLAGS)

Build the final executable
stock_analysis: $(OBJ)
    $(CC) -o $@ $(OBJ) $(CFLAGS) $(LIBS)

Clean compiled files
.PHONY: clean
clean:
    rm -f *.o stock_analysis
*/