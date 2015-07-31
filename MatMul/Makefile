# ############################
# LIST OF OBJECTS/EXES
# ############################
PERF = matmul0_perf.out matmul1_perf.out matmul1_omp_perf.out matmul2_perf.out matmulblock_perf.out matmulmkl_perf.out
VALIDATE = matmul0_validate.out matmul1_validate.out matmul1_omp_validate.out matmul2_validate.out matmulblock_validate.out
SCALING = matmul0_scaling.out matmul1_scaling.out matmul1_omp_validate.out matmul2_scaling.out matmulblock_scaling.out
EXES = $(PERF) $(VALIDATE) $(SCALING)
EXE_EXTENSION = .out

CPP = g++
REPEAT = 10
PARALLEL = yes

CENTOS = 6
ifeq ($(CPP),g++)
	CPPFLAGS = -g -O3 -march=native --std=c++11 -m64
else
	CPPFLAGS = -g -O3 -xHost -std=c++11 -vec-report
endif
ifeq ($(PARALLEL),yes)
	CPPFLAGS += -fopenmp 
	MKL_LIBRARIES =  -L$(MKLROOT)/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -ldl -lpthread -lm
else
	MKL_LIBRARIES =  -L$(MKLROOT)/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_sequential -lpthread -lm
endif
CFLAGS = $(CPPFLAGS)
LIBRARIES = -lrt
GLOBAL_DEPEND = matmul_utils.h Makefile
DEFINES = -DREPEAT=$(REPEAT) -DCONTIGUOUS

all:: $(EXES)
perf:: $(PERF)
validate:: $(VALIDATE)
scaling:: $(SCALING)

clean:
	rm -rf $(EXES) $(OBJECTS) *.o *.openss *.txt *.out *.bin

matmul0_perf.out: %$(EXE_EXTENSION) : matmul_perf.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_perf.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul0
matmul0_validate.out: %$(EXE_EXTENSION) : matmul_validate.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_validate.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul0
matmul0_scaling.out: %$(EXE_EXTENSION) : matmul_scaling.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_scaling.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul0

matmul1_perf.out: %$(EXE_EXTENSION) : matmul_perf.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_perf.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul1
matmul1_validate.out: %$(EXE_EXTENSION) : matmul_validate.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_validate.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul1
matmul1_scaling.out: %$(EXE_EXTENSION) : matmul_scaling.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_scaling.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul1

matmul1_omp_perf.out: %$(EXE_EXTENSION) : matmul_perf.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_perf.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul1_omp
matmul1_omp_validate.out: %$(EXE_EXTENSION) : matmul_validate.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_validate.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul1_omp
matmul1_omp_scaling.out: %$(EXE_EXTENSION) : matmul_scaling.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_scaling.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul1_omp

matmul2_perf.out: %$(EXE_EXTENSION) : matmul_perf.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_perf.cpp -o $*.out $(LIBRARIES) $(DEFINES)  $(MKL_LIBRARIES) -DMATMUL=matmul2
matmul2_validate.out: %$(EXE_EXTENSION) : matmul_validate.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_validate.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul2
matmul2_scaling.out: %$(EXE_EXTENSION) : matmul_scaling.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_scaling.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul2

matmulblock_perf.out: %$(EXE_EXTENSION) : matmul_perf.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_perf.cpp -o $*.out $(LIBRARIES) $(DEFINES)  $(MKL_LIBRARIES) -DMATMUL=matmul_block
matmulblock_validate.out: %$(EXE_EXTENSION) : matmul_validate.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_validate.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul_block
matmulblock_scaling.out: %$(EXE_EXTENSION) : matmul_scaling.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_scaling.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul_block

matmulblock2_perf.out: %$(EXE_EXTENSION) : matmul_perf.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_perf.cpp -o $*.out $(LIBRARIES) $(DEFINES)  $(MKL_LIBRARIES) -DMATMUL=matmul_block2
matmulblock2_validate.out: %$(EXE_EXTENSION) : matmul_validate.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_validate.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul_block2
matmulblock2_scaling.out: %$(EXE_EXTENSION) : matmul_scaling.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_scaling.cpp -o $*.out $(LIBRARIES) $(DEFINES) $(MKL_LIBRARIES) -DMATMUL=matmul_block2

matmulmkl_perf.out: %$(EXE_EXTENSION) : matmul_perf.cpp $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) $(LDFLAGS) matmul_perf.cpp -o $*.out $(LIBRARIES) $(DEFINES)  $(MKL_LIBRARIES) -DMATMUL=matmul_mkl

%.o: %.hpp %.cpp %.h $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) -c $*.cpp -o $*.o

%.o: %.cpp %.h $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CPPFLAGS) -c $*.cpp -o $*.o

%.o: %.c %.h $(GLOBAL_DEPEND)
	$(MODULE_CMDS) $(CPP) $(CFLAGS) -c $*.cpp -o $*.o

