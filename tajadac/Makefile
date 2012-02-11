SHELL    = bash
CC       = gcc
CCOPTS   = -g -Wall -D_GNU_SOURCE
CXX      = g++
CXXOPTS  = -g -Wall -D_GNU_SOURCE --std=gnu++0x
LDLIBS   = re2
YACC     = bison
YACCOPTS = --warnings=all --report=all

c++-build-obj = $(CXX) $(CXXOPTS) -c $<
c++-build-exe = $(CXX) $(CXXOPTS) -o $@ $^ $(LDLIBS:%=-l%)

.PHONY: all clean
all: tajadac
clean:
	rm -f ./*.o ./*.gch ./*.out ./*.yy token-bison-defs tajadac

# Executables
tajadac         : tajadac.o         ; $(c++-build-exe)
token-bison-defs: token-bison-defs.o; $(c++-build-exe)

# Objects
tajadac.o         : tajadac.cpp tokens.hpp macros.hpp parser.hpp; $(c++-build-obj)
token-bison-defs.o: token-bison-defs.cpp tokens.hpp macros.hpp  ; $(c++-build-obj)

# Token list for Bison input
token-bison-defs.out: token-bison-defs
	./$< > $@

# Bison input
parser.yy: parser.y token-bison-defs.out
	printf "%s\n" '/^%tokens$$/r token-bison-defs.out' '/^%tokens$$/d' 'w parser.yy' 'q' | ed -s parser.y

# Bison output
parser.hpp: parser.yy
	$(YACC) $(YACCOPTS) $<
