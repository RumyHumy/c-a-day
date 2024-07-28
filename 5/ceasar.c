#include <stdio.h>
#include <limits.h>

char str_to_int(char *str, int *out) {

	long int long_out = 0;
	char sign = 0;

	if (str == NULL || *str == '\0') {
		printf("Incorrect number. Empty string\n");
		return 0;
	}
	
	if (*str == '-' || *str == '+') {
		if (*str == '-')
			sign = 1;
		str++;
	}
	
	int i = 0;
	while (*str) {
		if (i == 10) {
			printf("Incorrect number. Out of range number\n");
			return 0;
		}
		if (*str < '0' || *str > '9') {
			printf("Incorect number. Unexpected char\n");
			return 0;
		}
		long_out *= 10;
		long_out += (*str-'0');
		str++;
		i++;
	}
	
	if (sign)
		long_out = -long_out;
	
	if (long_out > INT_MAX || long_out < INT_MIN) {
		printf("Incorrect number. Out of range number\n");
		return 0;
	}

	*out = long_out;
	
	return 1;
}

int main(int argc, char *argv[]) {
	
	if (argc < 3) {
		printf("Error. Not enough arguments.\n");
		return 1;
	}

	int shift = 0;
	if (!str_to_int(argv[1], &shift)) {
		printf("Error. Incorrect number.\n");
		return 1;
	}

	if (shift < -26 || shift > 26) {
		printf("Error. Shift value out of range\n");
		return 1;
	}
	
	char *ptr = argv[2];
	while (*ptr) {

		if (*ptr >= 'a' && *ptr <= 'z')
			*ptr = (((int)*ptr+shift-'a'+26)%26)+'a';
		else if (*ptr >= 'A' && *ptr <= 'Z')
			*ptr = (((int)*ptr+shift-'A'+26)%26)+'A';	

		ptr++;
	}
	
	printf("%s\n", argv[2]);

	return 0;
}
