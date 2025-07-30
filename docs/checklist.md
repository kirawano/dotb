- [x] implement text rendering
- [x] tic tac toe game + AI 
- [x] dialogue logic
- [x] timer implementation
- [ ] game end screen transition
- [x] gamestate logic
- [x] cross compilation
- [ ] integrate tic tac toe with GUI

### Code Fragmentation
Currently ``main.c`` feels more unreadable than it needs to be. It feels like most of the "meat" of the code (the main function) is surrounded by boilerplate that could be macro'd out of existence.

#### May 23rd 2025
I want to implement game logic first to actually have a good product before I start worrying about unreadable code, so I'm gonna work on that for the rest of today.

#### July 28th, 2025
I've split the code into 2 main files: an abstracted frontend that handles game logic and calls a renderer in the backend. 

