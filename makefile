CC := gcc
CFLAGS := -Wall -g -w

SRCS := prime.c queue.c activeObject.c pipeline.c
OBJS := $(SRCS:.c=.o)
EXEC := st_pipeline

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS) task.h
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJS)
