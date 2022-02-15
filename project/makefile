CC = gcc
CFLAGS =
LDFLAGS =  -lpthread

.SUFFIXES : .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<

ALL = chats chatc chats_select chatc_mt

all: $(ALL)

chats: chats.o 
	$(CC) -o $@ $< $(LDFLAGS)

chatc: chatc.o 
	$(CC) -o $@ $< $(LDFLAGS)

chats_select: chats_select.o 
	$(CC) -o $@ $< $(LDFLAGS)

chatc_mt: chatc_mt.o 
	$(CC) -o $@ $< $(LDFLAGS)

clean :
	rm -rf *.o $(ALL)
