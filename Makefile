CC = gcc
CFLAGS = -Wall -std=c99
TARGET = main.exe
SRC = main.c

.PHONY: clean run 

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	powershell -Command "if (Test-Path '$(TARGET)') { Remove-Item '$(TARGET)' }"
	@echo Clean completed

run: $(TARGET)
	$(TARGET)
	@echo Run successful

