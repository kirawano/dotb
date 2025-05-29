OBJS = dotb.c

CC = clang

LINKER_FLAGS = -lSDL2

COMPILER_FLAGS = -Wextra -g2 `pkg-config --cflags sdl2`


OBJ_NAME = dotb

all: $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

windows: $(OBJS) 
	export PKG_CONFIG_PATH=/usr/x86_65-w64-mingw32/lib/pkgconfig
	x86_64-w64-mingw32-gcc dotb-win.c $(COMPILER_FLAGS) $(LINKER_FLAGS) -o dotb.exe

clean:
	rm $(OBJ_NAME)
	rm dotb.exe
