SHELL = bash

clean =               \
        ./**/*.gch    \
        ./**/*.gen.*  \
        ./**/*.out    \
        ./**/*.output \
        ./parser.yy   \
        dep           \
        location.hh   \
        obj           \
        parser.dot    \
        parser.tab.cc \
        parser.tab.hh \
        parser.xml    \
        position.hh   \
        stack.hh      \
        tajadac       \



all:

clean:
	@echo "Cleaning"
	@shopt -s globstar && rm -rf $(clean)

%:
	@$(MAKE) --no-print-directory -f Makefile.real $@
