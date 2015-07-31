# ############################
# LIST OF OBJECTS/EXES
# ############################
PERF = pi-mc-1.out pi-mc-2.out
EXES = $(PERF) 
EXE_EXTENSION = .out

CC = mpicc
CFLAGS = -g
LFLAGS = -lm
GLOBAL_DEPEND = Makefile

all:: $(EXES)
perf:: $(PERF)
clean:
	rm -rf $(EXES) $(OBJECTS) *.o *.openss *.txt *.out *.bin

%.o: %.c %.h $(GLOBAL_DEPEND)
	$(CC) $(CFLAGS) -c $*.c -o $*.o

%.out: %.c $(GLOBAL_DEPEND)
	$(CC) $(CFLAGS) $*.c -o $*.out $(LFLAGS)

