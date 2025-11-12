CC = gcc
CFLAGS = -Wall -std=c99
TARGET = main.exe
OBJS = main.o functions.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c functions.h
functions.o: functions.c functions.h

clean:
	del /Q $(OBJS) $(TARGET) 2>nul || exit 0

run:  $(TARGET)
	./$(TARGET)

.PHONY: clean run 
