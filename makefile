# Compiler and flags
CC = gcc
# C90 standard, all warnings, and pedantic for strict compliance
CFLAGS = -Wall -ansi -pedantic -Iinclude
# The final executable name
TARGET = bin/assembler

# Find all .c files in the src directory
SRCS = $(wildcard src/*.c)
# Replace the .c extension with .o to get object file names
OBJS = $(SRCS:.c=.o)

# Default rule: build the target
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	@mkdir -p bin # Create bin directory if it doesn't exist
	$(CC) $(OBJS) -o $(TARGET)
	@echo "Build successful! Executable is at $(TARGET)"

# Rule to compile a .c file into a .o object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleanup complete."

.PHONY: all clean