PAPER = gc64-arch-spec
TEX = $(wildcard *.tex)
BIB = $(PAPER).bib
FIGS = $(wildcard figures/*.pdf figures/*.png figures/*.jpg ./*.jpg)

.PHONY: all clean

$(PAPER).pdf: $(TEX) $(BIB)
	pdflatex $(PAPER)
	bibtex $(PAPER).aux
	pdflatex $(PAPER)
	pdflatex $(PAPER)
clean:
	rm -f *.aux *.bbl *.blg *.log *.out $(PAPER).pdf
