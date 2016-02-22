CC = gcc
CFLAGS = -Wall -std=c99
OUTFILE = randmst
OBJS = prim.o
SRCS = prim.c
LIBS = -lm
$(OUTFILE): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(OBJS) $(LIBS)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
