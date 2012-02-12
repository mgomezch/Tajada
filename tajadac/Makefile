SHELL    = bash
CC       = gcc
CCOPTS   = -g -Wall -D_GNU_SOURCE
CXX      = g++
CXXOPTS  = -g -Wall -D_GNU_SOURCE --std=gnu++0x
LDLIBS   = re2
YACC     = bison
YACCOPTS = --warnings=all --report=all

%.o: %.cc; $(CXX) $(CXXOPTS) -c "./$<"
%  : %.o ; $(CXX) $(CXXOPTS) -o "$@" $^ $(LDLIBS:%=-l%)

.PHONY: all clean
all: tajadac
clean:
	rm -f ./*.o ./*.gch ./*.out ./*.yy tajadac location.hh parser.output parser.tab.cc parser.tab.hh position.hh stack.hh

tajadac     : main.o lex.o parser.tab.o
	$(CXX) $(CXXOPTS) -o "$@" $^ $(LDLIBS:%=-l%)

main.o      : main.cc lex.hh tokens.hh parser.tab.hh stack.hh location.hh position.hh
lex.o       : lex.cc         tokens.hh parser.tab.hh stack.hh location.hh position.hh
parser.tab.o: parser.tab.cc            parser.tab.hh stack.hh location.hh position.hh

location.hh parser.tab.cc parser.tab.hh position.hh stack.hh: parser.y tdefs.cc tokens.hh
	$(CXX) $(CXXOPTS) -E -P tdefs.cc | sed 's/ \?\! \?/\n/g' | sed -e '/^UNION void|/d' -e 's/^TOKEN void|\(%token \)<[^>]*> \(.*\)/\1\2/' -e 's/^UNION [^|]*|/        /' -e 's/^[^|]*|//' -e '/^$$/d' > tdefs.out
	printf '%s\n' '/^%tokens$$/r tdefs.out' '/^%tokens$$/d' 'w $<y' 'q' | ed -s $<
	$(YACC) $(YACCOPTS) $<y
	if [ "$$($(YACC) -V | head -n 1)" = 'bison (GNU Bison) 2.4.1' ]; then printf '%s\n' '/||\(.*\)/s//||(\1)/' wq | ed -s position.hh; fi
