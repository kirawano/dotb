OBJS = $(shell find . -name 'main.c')

CC = clang

LINKER_FLAGS = -lraylib

COMPILER_FLAGS = -Wextra -g2

OBJ_NAME = dotb

.PHONY: all clean

all: $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
