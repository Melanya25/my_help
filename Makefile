CC = gcc
CFLAGS = -I. -Wall -pthread
SOURCES = main.c mongoose.c
TARGET = server

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) *.o
