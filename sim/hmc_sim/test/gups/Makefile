#!/bin/sh
#
# HMCSIM TEST APPLICATIONS 
#
# TEST: GUPS
# ---------------------------------------

include ../Makefile.inc

SRC=./src

all: gups
gups:
	$(CC) $(CFLAGS) -o $@ $(SRC)/gups.c $(LDFLAGS) $(LDLIBS)
clean: 
	rm -Rf ./gups ./src/*.o
