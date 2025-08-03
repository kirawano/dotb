## July 29th, 2025
I initially thought I was, going to modify some of the functions to not modify global variables, instead having a pointer to a parameter that's passed through. This will make the code cleaner and more sectioned.

Instead, I may just lock any rendering logic to ``backend.c``, which will formalize what I was doing before. This takes less time and is more neat. I'm still going to do the former approach for ``dotb.c`` though.

## July 30th, 2025
- [x] integrate tic tac toe with ``dotb.c``
- [x] handle drawing of multiple backgrounds for different scenes
- [ ] implement mouse-based UI with options for tic tac toe and dialogue
- [x] make background dynamic to notify player when new dialogue is queued

## August 3rd, 2025
- [ ] implement mouse-based UI with options for tic tac toe and dialogue
- [ ] implement end screen transition that keeps you in the end screen if the game is beaten
- [ ] clean up code for better state handling and such
- [ ] cross compile and make "final" build of game
