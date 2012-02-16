SHELL    = bash

CC       = gcc
CCOPTS   = -g -Wall $(DEFINES:%=-D%)

CXX      = g++
CXXOPTS  = -g -Wall $(DEFINES:%=-D%) --std=gnu++0x

YACC     = bison
YACCOPTS = --warnings=all --report=all -g -x

CPP      = gcc -E
CPPOPTS  = -P

LDLIBS   = re2
DEFINES  = _GNU_SOURCE TAJADA_DEBUG

build-obj  = $(CXX) $(CXXOPTS) -c ./$<
build-exec = $(CXX) $(CXXOPTS) -o $@ $^ $(LDLIBS:%=-l%)

%.o: %.cc; $(build-obj)
%  : %.o ; $(build-exec)

.PHONY: all clean
all: tajadac
clean:
	rm -f ./*.o ./*.gch ./*.out ./*.yy tajadac location.hh parser.dot parser.output parser.tab.cc parser.tab.hh parser.xml position.hh stack.hh

tajadac : ast.o lex.o main.o parser.tab.o scope.o type.o ; $(build-exec)

#          .o:           .cc tokens.hh scope.hh ast.hh type.hh lex.hh debug.hh parser.tab.hh stack.hh location.hh position.hh
        ast.o:        ast.cc                    ast.hh type.hh
        lex.o:        lex.cc tokens.hh                         lex.hh debug.hh parser.tab.hh stack.hh location.hh position.hh
       main.o:       main.cc tokens.hh                         lex.hh          parser.tab.hh stack.hh location.hh position.hh
 parser.tab.o: parser.tab.cc           scope.hh ast.hh type.hh                 parser.tab.hh stack.hh location.hh position.hh
      scope.o:      scope.cc           scope.hh        type.hh
       type.o:       type.cc                           type.hh

location.hh parser.dot parser.output parser.tab.cc parser.tab.hh parser.xml position.hh stack.hh token_data.out token_data_line.out: parser.y tokens.hh Makefile
	@printf '%s\n'                                                                    \
                '#include "tokens.hh"'                                                    \
                '#define X(tag, description, r, type) type|%token@<tag>@tag@description!' \
                'TAJADA_TOKEN_DATA(X)'                                                    \
                | $(CPP) $(CPPOPTS) -                                                     \
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
                | $(CPP) $(CPPOPTS) -                        \
                | sed 's/ \?! \?/\n/g'                       \
                | sed                                        \
                        -e '/^void|/d'                       \
                        -e 's/^[^|]*|/        /'             \
                        -e '/^$$/d'                          \
                | column -t -s @                             \
                >> token_data.out
	@printf '%s\n' '}' >> token_data.out
	@tr -d '\n' < token_data.out > token_data_line.out
	@echo >> token_data_line.out
	@printf '%s\n'                                            \
                '1s@.*@@'                                         \
                '1s@$$@/* THIS FILE WAS AUTOMATICALLY GENERATED@' \
                '1s@$$@ BY THE BUILD SCRIPTS USING THE CONTENTS@' \
                '1s@$$@ OF “tokens.hh” AND “parser.y”; EDIT@'     \
                '1s@$$@ THOSE FILES INSTEAD OR YOUR CHANGES@'     \
                '1s@$$@ WILL BE LOST ONCE IT’S REGENERATED */@'   \
                '/^%token_data$$/r token_data_line.out'           \
                '/^%token_data$$/d'                               \
                'w $<y'                                           \
                'q'                                               \
                | ed -s ./$<
	$(YACC) $(YACCOPTS) ./$<y
	@if [ "$$($(YACC) -V | head -n 1)" = 'bison (GNU Bison) 2.4.1' ]; then printf '%s\n' '/||\(.*\)/s//||(\1)/' wq | ed -s position.hh; fi
