CC = gcc
CFLAGS = -Wall -O2

LIBS = -lSDL2

TARGET = rain
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean