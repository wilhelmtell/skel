.PHONY: all clean distclean

all: {NAME}.pdf
clean:
	rm -f {NAME}.log {NAME}.aux
distclean: clean
	rm -f {NAME}.pdf
{NAME}.pdf: {NAME}.tex
	xelatex -file-line-error -interaction=nonstopmode $^
