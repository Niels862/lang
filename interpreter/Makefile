BINARY=interpret
CODEDIRS=./ ../inc/ ../inc/types/

CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -I../inc/ -I../inc/types/ -MP -MD
CFILES=$(foreach D, $(CODEDIRS), $(wildcard $(D)*.c))
OBJECTS=$(patsubst %.c, %.o, $(CFILES))
DEPFILES=$(patsubst %.c, %.d, $(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(info $(CFILES))
	$(CC) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f $(BINARY) $(OBJECTS)

-include $(DEPFILES)
