#!/bin/sh
#
# HMCSIM TEST APPLICATIONS 
#
# TEST: PHYSRAND
# ---------------------------------------

include ../Makefile.inc

SRC=./src

all: physrand
physrand:
	$(CC) $(CFLAGS) -o $@ $(SRC)/physrand_main.c $(LDFLAGS) $(LDLIBS)
clean: 
	rm -Rf ./physrand ./src/*.o
