#!/bin/sh
#
# MEMSIM TEST APPLICATIONS
#
# TEST: SIMPLE
# ------------------------------------------

include ../Makefile.inc

SRC=./src

all: simple
simple:
	@echo " Building $(SRC)/simple.c"; $(CC) $(CFLAGS) -o $@ $(SRC)/simple.c $(LDFLAGS) $(LDLIBS)
clean:
	rm -Rf ./simple ./src/*.o
