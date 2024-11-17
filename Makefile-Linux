# filemenu.c and binaryflow.c and logflow are the source files
# compile each source file

CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm -lgmp -lmpfr
SOURCES = filemenu.c binaryflow.c logflow.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = filemenu binaryflow logflow

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) filemenu.o -o filemenu $(LDFLAGS)
	$(CC) binaryflow.o -o binaryflow $(LDFLAGS)
	$(CC) logflow.o -o logflow $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)


# vim: set ts=8 sw=8 noexpandtab:

#CC = gcc
#CFLAGS = -g -Wall
#LDFLAGS = -lm -lgmp -lmpfr
#SOURCES = filemenu.c
#OBJECTS = $(SOURCES:.c=.o)
#EXECUTABLE = filemenu

#all: $(SOURCES) $(EXECUTABLE)

#$(EXECUTABLE): $(OBJECTS)
#	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

#.c.o:
#	$(CC) $(CFLAGS) -c $< -o $@

#clean:
#	rm -f $(OBJECTS) $(EXECUTABLE)

# vim: set ts=8 sw=8 noexpandtab:
