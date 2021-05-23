#include <stdio.h>
#include <string.h>

#define NAME_MAX (255)

int main(int argc, char *argv[]) {

	FILE *fp;
	char c, filename[NAME_MAX + 1];

	strncpy(filename, argv[0], strlen(argv[0]));
	strncpy(filename + strlen(argv[0]), ".c", 3);

	if((fp = fopen(filename, "r")) != NULL) {
		while((c = fgetc(fp)) != EOF) {
			putc(c, stdout);
		}
	} else {
		printf("could not open file [%s]", filename);
	}

	return 0;
}
