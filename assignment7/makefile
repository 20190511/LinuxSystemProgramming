CC = gcc
CFLAGS =
LDFLAGS = -lpthread

.SUFFIXES : .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<

ALL = square mywc stricmp count new
all: $(ALL)

square: square.o
	$(CC) -o $@ $< $(LDFLAGS)

mywc: mywc.o
	$(CC) -o $@ $< $(LDFLAGS)

stricmp: stricmp.o	
	$(CC) -o $@ $< $(LDFLAGS)

count: count.o	
	$(CC) -o $@ $< $(LDFLAGS)
new: new.o	
	$(CC) -o $@ $< $(LDFLAGS)
clean :
	rm -rf *.o $(ALL)

