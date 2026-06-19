CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -I. -Ilib -Iinclude

SRC = \
	src/main.c \
	lib/lwjson/lwjson.c \
	lib/lwjson/lwjson_serializer.c \
	lib/lwjson/lwjson_utils.c \
	lib/lwjson/lwjson_debug.c

TARGET = build/zz.exe

all:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f build/*
