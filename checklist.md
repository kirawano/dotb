- [x] implement text rendering
- [ ] tic tac toe game + AI 
- [x] dialogue logic
- [ ] timer implementation
- [ ] game end screen transition
- [ ] gamestate logic
- [ ] cross compilation

### Code Fragmentation
Currently ``main.c`` feels more unreadable than it needs to be. It feels like most of the "meat" of the code (the main function) is surrounded by boilerplate that could be macro'd out of existence.

#### May 23rd 2025
I want to implement game logic first to actually have a good product before I start worrying about unreadable code, so I'm gonna work on that for the rest of today.

### Cross Compilation
Cross compilation has been pretty difficult to figure out (first time doing something like this, and I don't have a formal CS education). Hard-copying the sdl header file directory into ``/usr/x86_64-w64-mingw32`` is hacky and doesn't even work.

(EDIT: the hard-copying hack thing was the problem, I had to configure SDL2 with said directory prefix)
