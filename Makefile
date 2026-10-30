# Makefile for Inverted Search project

CC      := gcc
CFLAGS  := -Wall -Wextra -g
TARGET  := inverted_search
SRCS    := $(wildcard *.c)
OBJS    := $(SRCS:.c=.o)
HDRS    := $(wildcard *.h)

.PHONY: all clean run help

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Build and run with the sample files
run: $(TARGET)
	./$(TARGET) file1.txt file2.txt file3.txt

help:
	@echo "Targets:"
	@echo "  make        - build the project ($(TARGET))"
	@echo "  make run    - build and run with sample files"
	@echo "  make clean  - remove object files and the $(TARGET) binary"
	@echo "Usage:"
	@echo "  ./$(TARGET) <file1.txt> <file2.txt> ..."

clean:
	rm -f $(OBJS) $(TARGET)
