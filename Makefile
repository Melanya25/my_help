CC = gcc
CFLAGS = -I./mongoose -Wall -O2
LDFLAGS = -L./mongoose -lmg
SOURCES = main.c mongoose/mongoose.c
OBJECTS = main.o mongoose/mongoose.o
all: server
server: $(OBJECTS)
    $(CC) -o $@ $^ $(LDFLAGS)
clean:
    rm -f server *.o

