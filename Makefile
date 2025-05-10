CC = gcc
CFLAGS = -I. -Wall -Wextra
SOURCES = src/main.c mongoose.c
TARGET = server

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
