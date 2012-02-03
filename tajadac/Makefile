CC      = gcc
CCOPTS  = -g -Wall -D_GNU_SOURCE
CXX     = g++
CXXOPTS = -g -Wall -D_GNU_SOURCE --std=gnu++0x
LDLIBS  = -lre2

all: tajadac

clean:
	rm -f *.o tajadac

tajadac.o: tajadac.cpp
	$(CXX) $(CXXOPTS) -c $<

tajadac: tajadac.o
	$(CXX) $(CXXOPTS) -o $@ $^ $(LDLIBS)
