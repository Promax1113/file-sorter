# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = main
SRC = main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
	rm -rf $(TARGET).dSYM