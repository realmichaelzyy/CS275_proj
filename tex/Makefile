# DOCUMENT=main-yuanjie
DOCUMENT=main-yuanjie-v2

default: $(DOCUMENT).pdf

$(DOCUMENT).toc: $(DOCUMENT).tex
	pdflatex --shell-escape $(DOCUMENT).tex

$(DOCUMENT).pdf: $(DOCUMENT).toc
	bibtex $(DOCUMENT)
	pdflatex --shell-escape $(DOCUMENT).tex
	pdflatex --shell-escape $(DOCUMENT).tex

#--------------------------------------------------
# $(DOCUMENT).ps: $(DOCUMENT).dvi
# 	dvips -t letter -Ppdf -G0 -o $@ $<
# 
# $(DOCUMENT).pdf: $(DOCUMENT).ps
# 	cat $(DOCUMENT).ps | ps2pdf - > $(DOCUMENT).pdf 
#-------------------------------------------------- 

all: $(DOCUMENT).pdf

clean:
	rm -rf *.aux $(DOCUMENT).log $(DOCUMENT).toc \
     $(DOCUMENT).bbl $(DOCUMENT).blg $(DOCUMENT).pdf \
