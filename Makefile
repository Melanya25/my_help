CC = gcc
CFLAGS = -I./lib/mongoose -Wall -pthread
SOURCES = src/main.c lib/mongoose/mongoose.c
TARGET = server

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
