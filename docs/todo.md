## July 29th, 2025
I initially thought I was, going to modify some of the functions to not modify global variables, instead having a pointer to a parameter that's passed through. This will make the code cleaner and more sectioned.

Instead, I may just lock any rendering logic to ``backend.c``, which will formalize what I was doing before. This takes less time and is more neat. I'm still going to do the former approach for ``dotb.c`` though.

## July 30th, 2025
- [ ] integrate tic tac toe with ``dotb.c``
- [ ] handle drawing of multiple backgrounds for different scenes
- [ ] implement mouse-based UI with options for tic tac toe and dialogue
- [x] make background dynamic to notify player when new dialogue is queued
