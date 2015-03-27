# Example Makefile
# The C++ compiler

CPP = g++
CPPFLAGS = -DADD_ -O3 '-DCOMPLEX=std::complex<double>'

# The architecture
ARCH = linux

# The top-level SparseLib++ directory
SPARSELIB = ../libs/SparseLib-1.7
GSLLIB = ../libs/gsl-1.6

# The various include directories
IML_INCLUDE = $(SPARSELIB)/mv/include
MV_INCLUDE = $(SPARSELIB)/mv/include
SPARSELIB_INCLUDE = $(SPARSELIB)/include
GSL_INCLUDE = $(GSLLIB)/include

# A list of all include directives for the compiler
INCLUDES = -I$(IML_INCLUDE) -I$(MV_INCLUDE) -I$(SPARSELIB_INCLUDE) -I$(GSL_INCLUDE)

# The SparseLib++ library archive file
SPARSELIB_LIB = $(SPARSELIB)/lib
GSL_LIB = $(GSLLIB)/lib

# Libraries to be linked
LIBS = -L$(SPARSELIB_LIB) -lsparse -lspblas -lmv -L$(GSL_LIB) -lgsl -lgslcblas -lm -lrt
OBJS = Matio.o

# Rule to create executable from %.o
all : $(OBJS) mat2HB

# Rule to create object
mat2HB : $(OBJS)
	$(CPP) $(INCLUDES) $(CPPFLAGS) $(OBJS) -o mat2HB $(LIBS)
%.o : %.cc 
	$(CPP) $(INCLUDES) $(CPPFLAGS) -c $<
%.o : %.c
	$(CPP) $(INCLUDES) $(CPPFLAGS) -c $<
clean : 
	rm -f *.o mat2HB
