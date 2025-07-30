- [x] implement text rendering
- [ ] tic tac toe game + AI 
- [x] dialogue logic
- [x] timer implementation
- [ ] game end screen transition
- [x] gamestate logic
- [x] cross compilation

### Code Fragmentation
Currently ``main.c`` feels more unreadable than it needs to be. It feels like most of the "meat" of the code (the main function) is surrounded by boilerplate that could be macro'd out of existence.

#### May 23rd 2025
I want to implement game logic first to actually have a good product before I start worrying about unreadable code, so I'm gonna work on that for the rest of today.

#### July 28th, 2025
I've split the code into 2 main files: an abstracted frontend that handles game logic and calls a renderer in the backend. 

### Plans
#### July 29th, 2025
I initially thought I was, going to modify some of the functions to not modify global variables, instead having a pointer to a parameter that's passed through. This will make the code cleaner and more sectioned.

Instead, I may just lock any rendering logic to ``backend.c``, which will formalize what I was doing before. This takes less time and is more neat. I'm still going to do the former approach for ``dotb.c`` though.

