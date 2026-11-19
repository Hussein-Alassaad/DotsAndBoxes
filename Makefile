CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic -g -O0
TARGET  = dotsandboxes
SRCS    = main.c board.c game.c display.c input.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean run valgrind gdb install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c display.h game.h board.h input.h
board.o: board.c board.h
game.o: game.c game.h board.h
display.o: display.c display.h game.h board.h
input.o: input.c input.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

gdb: $(TARGET)
	gdb ./$(TARGET)

# Copies the game to /usr/local/bin so it can be launched at boot.
install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin/$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
