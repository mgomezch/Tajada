pandoc := pandoc

pandocflags :=              \
        --normalize         \
        --number-sections   \
        --preserve-tabs     \
        --section-divs      \
        --standalone        \
        --table-of-contents

formats := txt html pdf

clean-formats := aux log out toc

pandoc-latex-args := --latex-engine=xelatex -H header.tex

files := $(formats:%=especificación.%)

pandocrule = \
        sed < $<                                                   \
                -e '/^@@\/\//d'                                    \
                -e 's/^@\(@[^@]\+\)*@$(suffix $@)\(@[^@]\+\)*@@//' \
                -e '/^@\(@[^@]\+\)\+@@/d'                          \
        | $(pandoc) $(pandocflags) -o $@



.PHONY: all clean

all: $(files)

clean:
	rm -f $(clean-formats:%=*.%) $(files)



%.txt : %.md ; $(pandocrule)
%.html: %.md ; $(pandocrule)
%.pdf : %.md ; $(pandocrule) $(pandoc-latex-args)
%.tex : %.md ; $(pandocrule) $(pandoc-latex-args)

especificación.pdf especificación.tex: header.tex
