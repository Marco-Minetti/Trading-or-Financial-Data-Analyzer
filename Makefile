# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -c -lm  # Add math library (-lm) for compilation
LDFLAGS = -lm  # Link math library

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files (excluding csv_reader and parallel_processing)
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/data_structures.c \
       $(SRC_DIR)/analytics.c \
       $(SRC_DIR)/query_interface.c \
	   $(SRC_DIR)/binary_io.c

# Object files (replace .c with .o)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Output binary
TARGET = $(BIN_DIR)/financial_analyzer

# Default target
all: $(TARGET)

# Create binary from object files
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Create necessary directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the program
run: all
	./$(TARGET)