PAPER = gc64-arch-spec
TEX = $(wildcard *.tex)
BIB = sample.bib
FIGS = $(wildcard figures/*.pdf figures/*.png figures/*.jpg ./*.jpg)

.PHONY: all clean

$(PAPER).pdf: $(TEX) 
	pdflatex $(PAPER)
	pdflatex $(PAPER)
	pdflatex $(PAPER)
clean:
	rm -f *.aux *.bbl *.blg *.log *.out $(FINAL).pdf $(PAPER).pdf
