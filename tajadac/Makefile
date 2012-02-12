SHELL    = bash
CC       = gcc
CCOPTS   = -g -Wall -D_GNU_SOURCE
CPP      = gcc -E -P
CXX      = g++
CXXOPTS  = -g -Wall -D_GNU_SOURCE --std=gnu++0x
LDLIBS   = re2
YACC     = bison
YACCOPTS = --warnings=all --report=all

%.o: %.cc; $(CXX) $(CXXOPTS) -c ./$<
%  : %.o ; $(CXX) $(CXXOPTS) -o $@ $^ $(LDLIBS:%=-l%)

.PHONY: all clean
all: tajadac
clean:
	rm -f ./*.o ./*.gch ./*.out ./*.yy tajadac location.hh parser.output parser.tab.cc parser.tab.hh position.hh stack.hh

tajadac     : main.o lex.o parser.tab.o
	$(CXX) $(CXXOPTS) -o $@ $^ $(LDLIBS:%=-l%)

main.o      : main.cc lex.hh tokens.hh parser.tab.hh stack.hh location.hh position.hh
lex.o       : lex.cc         tokens.hh parser.tab.hh stack.hh location.hh position.hh
parser.tab.o: parser.tab.cc            parser.tab.hh stack.hh location.hh position.hh

location.hh parser.tab.cc parser.tab.hh position.hh stack.hh: parser.y tokens.hh Makefile
	@printf '%s\n'                                                                    \
                '#include "tokens.hh"'                                                    \
                '#define X(tag, description, r, type) type|%token@<tag>@tag@description!' \
                'TAJADA_TOKEN_DATA(X)'                                                    \
                | $(CPP) -                                                                \
                | sed 's/ \?! \?/\n/g'                                                    \
                | sed                                                                     \
                        -e 's/^void|\(%token@\)<[^>]*>\(@[^ ]*@\)u8\(.*\)$$/\1 \2\3/'     \
                        -e 's/^[^|]*|\(%token@<[^>]*>@[^ ]*@\)u8\(.*\)$$/\1\2/'           \
                        -e 's/" u8"//g'                                                   \
                | column -t -s @                                                          \
                > token_data.out
	@printf '%s\n'     \
                ''         \
                '%union {' \
                >> token_data.out
	@printf '%s\n'                                       \
                '#include "tokens.hh"'                       \
                '#define X(tag, d, r, type) type|type@tag;!' \
                'TAJADA_TOKEN_DATA(X)'                       \
                | $(CPP) -                                   \
                | sed 's/ \?! \?/\n/g'                       \
                | sed                                        \
                        -e '/^void|/d'                       \
                        -e 's/^[^|]*|/        /'             \
                        -e '/^$$/d'                          \
                | column -t -s @                             \
                >> token_data.out
	@printf '%s\n' '}' >> token_data.out
	@printf '%s\n'                                            \
                '1i'                                              \
                '/*********************************************'  \
                ' *   THIS FILE WAS AUTOMATICALLY GENERATED   *'  \
                ' *  BY THE BUILD SCRIPTS USING THE CONTENTS  *'  \
                ' *       OF “tokens.hh” AND “parser.y”       *'  \
                ' *********************************************/' \
                ''                                                \
                '.'                                               \
                '/^%tokens$$/r token_data.out'                    \
                '/^%tokens$$/d'                                   \
                'w $<y'                                           \
                'q'                                               \
                | ed -s ./$<
	$(YACC) $(YACCOPTS) ./$<y
	@if [ "$$($(YACC) -V | head -n 1)" = 'bison (GNU Bison) 2.4.1' ]; then printf '%s\n' '/||\(.*\)/s//||(\1)/' wq | ed -s position.hh; fi
