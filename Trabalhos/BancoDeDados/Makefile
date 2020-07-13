SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
MAIN := main.c
CFLAGS := -Wall -Wextra -Wpedantic
TARGET := sgbd

all: $(OBJFILES)
	gcc $(MAIN) $(SRC_FILES) -o $(TARGET) $(CFLAGS)

clean:
	rm -r $(TARGET)

debug:
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)
