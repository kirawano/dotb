OBJS = $(shell find . -name '*.c')

CC = clang

LINKER_FLAGS = -lSDL2

COMPILER_FLAGS = -Wextra -g2 `pkg-config --cflags sdl2`

OBJ_NAME = dotb

.PHONY: all clean

all: $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
	rm $(OBJ_NAME).exe
