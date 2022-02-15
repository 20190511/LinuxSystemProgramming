CC = gcc
CFLAGS =
LDFLAGS = -lpthread

.SUFFIXES : .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<

ALL = fork1 fork exit wait race worace env exec system thread cmd_i cmd_p cmd_t mysystem tadd

all: $(ALL)

fork1: fork1.o
	$(CC) -o $@ $< $(LDFLAGS)

fork: fork.o
	$(CC) -o $@ $< $(LDFLAGS)

exit: exit.o
	$(CC) -o $@ $< $(LDFLAGS)

wait: wait.o
	$(CC) -o $@ $< $(LDFLAGS)

race: race.o
	$(CC) -o $@ $< $(LDFLAGS)

worace: worace.o
	$(CC) -o $@ $< $(LDFLAGS)

env: env.o
	$(CC) -o $@ $< $(LDFLAGS)

exec: exec.o
	$(CC) -o $@ $< $(LDFLAGS)

system: system.o
	$(CC) -o $@ $< $(LDFLAGS)

thread: thread.o
	$(CC) -o $@ $< $(LDFLAGS)

cmd_i: cmd_i.o
	$(CC) -o $@ $< $(LDFLAGS)

cmd_p: cmd_p.o
	$(CC) -o $@ $< $(LDFLAGS)

cmd_t: cmd_t.o
	$(CC) -o $@ $< $(LDFLAGS)

mysystem: mysystem.o
	$(CC) -o $@ $< $(LDFLAGS)

tadd: tadd.o
	$(CC) -o $@ $< $(LDFLAGS)

clean :
	rm -rf *.o $(ALL)
