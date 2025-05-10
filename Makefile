CC = gcc
CFLAGS = -I. -Wall
SOURCES = src/main.c src/input.c mongoose/mongoose.c
OBJECTS = $(SOURCES:.c=.o)

all: server

server: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f server $(OBJECTS)
