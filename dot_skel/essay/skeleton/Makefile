.PHONY: all clean distclean

SRC := {NAME}.tex
PDF := $(SRC:.tex=.pdf)
LOG := $(SRC:.tex=.log)
AUX := $(SRC:.tex=.aux)

all: $(PDF)
clean:
	rm -f $(LOG) $(AUX)
distclean: clean
	rm -f $(PDF)
%.pdf: %.tex
	xelatex -halt-on-error -file-line-error -interaction=nonstopmode $^
