OBJS = src/*.c
CC = gcc
OBJ_NAME = main
COMPILER_FLAGS = -w

all: $(OBJS)
	$(CC) $(OBJS)  -o $(OBJ_NAME)