CC = gcc
CFLAGS =
LDFLAGS = -lpthread

.SUFFIXES : .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<

ALL = lotto memo fifos sync server client

all: $(ALL)

lotto : lotto.o
	$(CC) -o $@ $^ $(LDFLAGS)
memo : memo.o
	$(CC) -o $@ $^ $(LDFLAGS)
fifos : fifos.o
	$(CC) -o $@ $^ $(LDFLAGS)
sync : sync.o synclib.o
	$(CC) -o $@ $^ $(LDFLAGS)
server : server.o
	$(CC) -o $@ $^ $(LDFLAGS)
client : client.o
	$(CC) -o $@ $^ $(LDFLAGS)
clean :
	rm -rf *.o $(ALL)
