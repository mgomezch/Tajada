CC       = gcc
CCOPTS   = -g -Wall -D_GNU_SOURCE
CXX      = g++
CXXOPTS  = -g -Wall -D_GNU_SOURCE --std=gnu++0x
LDLIBS   = re2
YACC     = bison
YACCOPTS = -t

execs   = tajadac

c++-build-obj = $(CXX) $(CXXOPTS) -c $<
c++-build-exe = $(CXX) $(CXXOPTS) -o $@ $^ $(LDLIBS:%=-l%)

.PHONY: all clean
all: $(execs)
clean: ; rm -f $(execs) ./*.o

tajadac  : tajadac.o  ; $(c++-build-exe)
tajadac.o: tajadac.cpp; $(c++-build-obj)
