CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra
LIBS = -lm

OBJS = main.o fb.o input.o phys.o level.o draw.o log.o

cDock: $(OBJS)
	$(CC) $(CFLAGS) -o cDock $(OBJS) $(LIBS)

clean:
	rm -f cDock $(OBJS)
