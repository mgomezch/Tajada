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



.DEFAULT_GOAL := all

.PHONY: force clean

clean:
	@echo "Cleaning"
	@shopt -s globstar && rm -rf $(clean)

%: force
	@$(MAKE) --no-builtin-variables --no-print-directory -f Makefile.real $@

Makefile force: ;
