// This program prints dialog box like
//
// ./moo.c text
//
// /------\
// | text |
// \ -----/
//  \|

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_line(char c, int count) {
	for (int i = 0; i < count; i++)
		printf("%c", c);
}

int main(int argc, char* argv[]) {

	if (argc < 2)
		return 1;
	
	int max_width = 10;
	if (max_width < 5)
		return 1;
	
	int str_size = strlen(argv[1]);
	int line_size = str_size;
		
	if (str_size+4 > max_width)
		line_size = max_width;

	printf("/");
	print_line('-', line_size+2);
	printf("\\\n");

	for (int i = 0; i < str_size; i += line_size) {
		printf("| ");	
		for (int j = 0; j < line_size; j++) {
			if (i+j >= str_size) {
				printf(" ");
				continue;
			}
			printf("%c", argv[1][i+j]);
		}
		printf(" |\n");
	}

	printf("\\ ");
	print_line('-', line_size+1);
	printf("/\n \\|\n");

	return 0;
}

