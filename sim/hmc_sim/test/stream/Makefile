#!/bin/sh
#
# HMCSIM TEST APPLICATIONS 
#
# TEST: STREAM
# ---------------------------------------

include ../Makefile.inc

SRC=./src

all: stream
$(SRC)/shiftamt.o: $(SRC)/shiftamt.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(SRC)/stream.o: $(SRC)/stream.c
	$(CC) $(CFLAGS) -c -o $@ $<
stream: $(SRC)/stream.o $(SRC)/shiftamt.o
	$(CC) $(CFLAGS) -o $@ $(SRC)/stream.o $(SRC)/shiftamt.o $(LDFLAGS) $(LDLIBS)
clean: 
	rm -Rf ./stream ./src/*.o
