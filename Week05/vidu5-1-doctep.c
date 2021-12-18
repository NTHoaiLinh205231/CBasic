#include "/media/sf_CBasic/cgen/ext/io.h"
#include<string.h>

typedef struct song_s {
	char *name;
	char *path;
} *song_t;

int main() {

	FILE *inp = fopen("songs.txt", "r");
	char *line = NULL;
	//char line[100]; //Not OK
	char *name;
	char *path;
	while (cgetline(&line, 0, inp)) {
		//printf("%s", line);
		if (line[strlen(line)-1] == '\n') {
			line[strlen(line)-1] = '\0';
		}
		for (int i = 0; i < strlen(line); ++i) {
			if (line[i] == '*' && line[i+1] == '#' && line[i+2] == '*') {
				path = line + i +3;
				line[i] = '\0';
				name = line;
				printf("%s\n%s\n", name, path);
			}
		}
	}
	fclose(inp);
	return 0;
}