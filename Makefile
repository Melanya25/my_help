CC = gcc
CFLAGS = -I. -Wall -pthread
SOURCES = src/main.c mongoose.c
TARGET = greeting_server

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) *.o

run: all
	./$(TARGET)
