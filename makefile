OBJS = main.c

CC = clang

LINKER_FLAGS = -lSDL2

COMPILER_FLAGS = -Wextra -g2 `pkg-config --cflags sdl2`

OBJ_NAME = dotb 

all: $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
	# rm *.o # just in case we have any leftovers in the future
