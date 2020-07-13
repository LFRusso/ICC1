SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
MAIN := main.c
CFLAGS := -Wall -Wextra -Wpedantic
TARGET := sgbd
OBJFILES := $(wildcard *.o)


all: objects
	gcc $(MAIN) $(OBJFILES) -o $(TARGET) $(CFLAGS)

objects:
	gcc $(SRC_FILES) -c

clean:
	rm -r $(OBJFILES) $(TARGET)

debug:
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)
