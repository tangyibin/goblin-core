#!/bin/sh
#
# HMCSIM TEST APPLICATIONS 
#
# TEST: STREAM
# ---------------------------------------

include ../Makefile.inc

SRC=./src

all: stream
stream:
	$(CC) $(CFLAGS) -o $@ $(SRC)/stream.c $(LDFLAGS) $(LDLIBS)
clean: 
	rm -Rf ./stream ./src/*.o
