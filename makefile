CC = gcc
CFLAGS = -Wall -Werror -std=c11
LDFLAGS = -lm

SRCS = compare.c findFiles.c queue.c jsd.c readfile.c

OBJS = $(SRCS:.c=.o)

compare: $(OBJS)
	$(CC) $(CFLAGS) -o compare $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) compare
