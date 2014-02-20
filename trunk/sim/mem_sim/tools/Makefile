#!/bin/sh
# 
# MEMSIM TOOLS
# 
# ----------------------------------------

include ./Makefile.inc

SRC=./src

all: memsimtognuplot
memsimtognuplot:
	@echo " Building memsimtognuplot"; $(CC) $(CFLAGS) -o $@ $(SRC)/memsimtognuplot.c $(LDFLAGS) $(LDLIBS)
clean:
	rm -Rf ./memsimtognuplot ./src/*.o
