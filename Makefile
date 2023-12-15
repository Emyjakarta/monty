CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c89

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
EXEC = monty

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
