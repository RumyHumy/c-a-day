# Project name
PROJECT=Test

# Include & lib directories
LDIR=-L/usr/lib
IDIR=-I/usr/include/SDL2

# Compiler flags
CFLAGS=$(IDIR) -std=c99 -Wall -g

# Linker flags
LDFLAGS=$(LDIR) -lSDL2 -lm

# Source files
SOURCES=main.c

# Object files
OBJECTS=$(SOURCES:.c=.o)

# Executable file
EXECUTABLE=$(PROJECT)

# Build the executable
all: $(EXECUTABLE)

# Build object files from source files
%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

# Link object files into executable
$(EXECUTABLE): $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@

# Clean up object files and executable
clean:
	rm -f $(CFLAGS) $(OBJECTS) $(EXECUTABLE)

# Run the executable
run: $(EXECUTABLE)
	./$(EXECUTABLE)
