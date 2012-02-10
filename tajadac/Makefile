SHELL    = bash
CC       = gcc
CCOPTS   = -g -Wall -D_GNU_SOURCE
CXX      = g++
CXXOPTS  = -g -Wall -D_GNU_SOURCE --std=gnu++0x
LDLIBS   = re2
YACC     = bison
YACCOPTS = -t

c++-build-obj = $(CXX) $(CXXOPTS) -c $<
c++-build-exe = $(CXX) $(CXXOPTS) -o $@ $^ $(LDLIBS:%=-l%)

.PHONY: all clean
all: tajadac
clean:
	rm -f ./*.o ./*.gch ./*.out ./*.yy token-bison-defs tajadac

tajadac             : tajadac.o                        ; $(c++-build-exe)
tajadac.o           : tajadac.cpp tokens.hpp macros.hpp; $(c++-build-obj)
token-bison-defs    : token-bison-defs.o               ; $(c++-build-exe)
token-bison-defs.o  : token-bison-defs.cpp tokens.hpp  ; $(c++-build-obj)

token-bison-defs.out: token-bison-defs
	./$< > $@

parser.yy: parser.y token-bison-defs.out
	printf "%s\n" '/^%tokens$$/r token-bison-defs.out' '/^%tokens$$/d' 'w parser.yy' 'q' | ed -s parser.y
