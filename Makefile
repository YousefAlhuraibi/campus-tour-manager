CC = gcc
CFLAGS = -g -Wall -pedantic-errors -std=c99
TARGET = campus-tour-manager

all: $(TARGET)
	$(CC) $(TARGET).c -o $(TARGET) $(CFLAGS)
	
clean:
	rm $(TARGET)
