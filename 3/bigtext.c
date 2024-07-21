// This program returns
// text

// Font file
// A
// .###.
// #...#
// #####
// #...#
// #...#
// B
// ...

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR_WIDTH 16
#define MAX_CHAR_HEIGHT 16
#define CHAR_COUNT 92

int main(int argc, char* argv[]) {
	
	if (argc < 2) {
		printf("Too few arguments.\n");
		return 1;
	}

	char char_pics[MAX_CHAR_HEIGHT][MAX_CHAR_WIDTH*CHAR_COUNT];

	FILE *fp;
	char buffer[MAX_CHAR_WIDTH+32];
	fp = fopen("font.txt", "r");

	if (fp == NULL) {
		printf("Error opening file.\n");
		return 1; 
	}

	int char_width = 0, char_height = 1;
	fgets(buffer, sizeof(buffer), fp);
	char_width = strlen(buffer)-1;
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		if (buffer[0] == '\n')
			break;
		char_height++;
	}

	//printf("%d %d\n", char_width, char_height);

	int line = 0;
	char curr = '\0';
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		int relative_line = line%(char_height+1);
		if (relative_line == 0) {
			curr = buffer[0];
		} else {
			for (int r = 0; r < char_width; r++) {
				char_pics[relative_line-1][MAX_CHAR_WIDTH*(curr-32)+r] = buffer[r];
			}
		}
		line++;
	}
	int str_size = strlen(argv[1]);
	for (int r = 0; r < char_height; r++) {
		for (int i = 0; i < str_size; i++) {
			for (int c = 0; c < char_width; c++) {
				printf("%c", char_pics[r][MAX_CHAR_WIDTH*(argv[1][i]-32)+c]);
			}
		}
		printf("\n");
	}

	fclose(fp);
	
	return 0;
}
