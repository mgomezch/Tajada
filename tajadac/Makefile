SHELL = bash

clean =               \
        ./**/*.d      \
        ./**/*.gch    \
        ./**/*.gen.*  \
        ./**/*.o      \
        ./**/*.out    \
        ./**/*.output \
        ./**/*.tab.cc \
        ./**/*.yy     \
        location.hh   \
        parser.dot    \
        parser.tab.cc \
        parser.tab.hh \
        parser.xml    \
        position.hh   \
        stack.hh      \
        tajadac       \

all:

clean:
	shopt -s globstar && rm -f $(clean)

%:
	@$(MAKE) --no-print-directory -f Makefile.real $@
