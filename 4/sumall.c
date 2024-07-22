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

	if (argc < 2) {
		printf("Not enough arguments.\n");
		return 1;
	}
	
	int sum = 0;
	for (int i = 1; i < argc; i++) {
		int n = 0;
		if (!str_to_int(argv[i], &n)) {
			printf("Error.\n");
			return 1;
		}
		if (sum > 0 && n > INT_MAX-sum || sum < 0 && n < INT_MIN-sum) {
			printf("Sum is too big/small. Error.\n");
			return 1;
		}
		sum += n;
	}

	printf("%d\n", sum);

	return 0;
}
