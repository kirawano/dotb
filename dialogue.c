#include <stdio.h>

static char * const dialogue_table[] = {
	[3] = "DON'T OPEN THE BOX.\nPLEASE, FOR MY SAKE",
	[4] = "LOOK WHO JUST OPENED THE BOX",
};

int get_dialogue(int time, const char **out){
	int dialogue_table_size = sizeof(dialogue_table)/sizeof(dialogue_table[0]);

	if (time < 0 || time >= dialogue_table_size){
		*out = NULL;
	 	return 0;
	}

	char *entry = dialogue_table[time];

	if (entry == NULL) {
		*out = NULL;
		return 0;
	}

	*out = entry;
	return 1;
}
