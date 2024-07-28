# gcc main.c -o Build -I/usr/include -L/usr/lib -lraylib -lm -lGL -lpthread -ldl -lrt -lX11 -std=c99

SOURCES = main.c dmatrix2.c
HEADERS = dmatrix2.h

OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = Build

CFLAGS = -Wall -g # -std=c99

LDFLAGS = -L/usr/lib -lraylib -lm -lGL -lpthread -ldl -lrt -lX11

CFLAGS += -I/usr/include -I. 

%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	gcc $(OBJECTS) $(LDFLAGS) -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
