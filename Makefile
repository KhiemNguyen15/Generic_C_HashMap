CC = gcc
CFLAGS = -I./include
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = hashmaprunner

all: $(EXECUTABLE)

$(EXECUTABLE): main.c $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
