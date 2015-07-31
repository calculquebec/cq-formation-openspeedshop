# ############################
# LIST OF OBJECTS/EXES
# ############################
PERF = io_problem0.out io_problem1.out io_problem2.out io_problem3.out io_problem4.out
EXES = $(PERF) 
EXE_EXTENSION = .out

CPP = g++
CPPFLAGS = -g --std=c++11 -fopenmp
GLOBAL_DEPEND = io_utils.h Makefile
all:: $(EXES)
perf:: $(PERF)
clean:
	rm -rf $(EXES) $(OBJECTS) *.o *.openss mydata.dat *.out *.bin

io_problem0.out: io_utils0.o io_problem.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) io_utils0.o io_problem.cpp -o $*.out $(DEFINES)

io_problem1.out: io_utils1.o io_problem.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) io_utils1.o io_problem.cpp -o $*.out $(DEFINES)

io_problem2.out: io_utils2.o io_problem.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) io_utils2.o io_problem.cpp -o $*.out $(DEFINES)

io_problem3.out: io_utils3.o io_problem.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) io_utils3.o io_problem.cpp -o $*.out $(DEFINES)

io_problem4.out: io_utils4.o io_problem.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) io_utils4.o io_problem.cpp -o $*.out $(DEFINES)

%.o: %.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) -c $*.cpp -o $*.o 


#%.out: %.cpp $(GLOBAL_DEPEND)
#	$(MODULE_CMDS) $(CC) $(CFLAGS) $*.cpp -o $*.out $(DEFINES)

