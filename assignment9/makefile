CC = gcc
CFLAGS =
LDFLAGS = -lpthread

.SUFFIXES : .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<

ALL = producer consumer producer_s consumer_s prodcons dining dining2 prodcons_m prodcons_s sipc1_sema sipc2_sema sipc_multiThread

all: $(ALL)

prodcons_t: prodcons_t.o
	$(CC) -o $@ $< $(LDFLAGS)

sipc_multiThread: sipc_multiThread.o
	$(CC) -o $@ $< $(LDFLAGS)

producer: producer.o 
	$(CC) -o $@ $< $(LDFLAGS)

consumer: consumer.o 
	$(CC) -o $@ $< $(LDFLAGS)

producer_s: producer_s.o semlib.o
	$(CC) -o $@ $^ $(LDFLAGS)

consumer_s: consumer_s.o semlib.o
	$(CC) -o $@ $^ $(LDFLAGS)

prodcons: prodcons.o
	$(CC) -o $@ $< $(LDFLAGS)

dining: dining.o
	$(CC) -o $@ $< $(LDFLAGS)

dining2: dining2.o
	$(CC) -o $@ $< $(LDFLAGS)

prodcons_m: prodcons_m.o
	$(CC) -o $@ $< $(LDFLAGS)

prodcons_s: prodcons_s.o semlib2.o
	$(CC) -o $@ $^ $(LDFLAGS)

sipc1_sema: sipc1_sema.o semlib.o
	$(CC) -o $@ $^ $(LDFLAGS)

sipc2_sema: sipc2_sema.o semlib.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean :
	rm -rf *.o $(ALL)
