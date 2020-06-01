CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0)
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

SRC = *.c

OBJS = $(SRC:.c=.o)

all: instalarch

%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<

instalarch: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)
	rm -f $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(@F)
