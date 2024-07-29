# gcc main.c -o Build -I/usr/include -L/usr/lib -lraylib -lm -lGL -lpthread -ldl -lrt -lX11 -std=c99

EXECUTABLE = Build

SOURCES = main.c dmatrix2.c ramenn.c unit_tests.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -g -std=c99

LDFLAGS = -L/usr/lib -lraylib -lm -lGL -lpthread -ldl -lrt -lX11

CFLAGS += -I/usr/include -I. 

$(EXECUTABLE): $(OBJECTS)
	gcc $(OBJECTS) $(LDFLAGS) -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(OBJECTS)
