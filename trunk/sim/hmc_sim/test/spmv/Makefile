#!/bin/sh
#
# HMCSIM TEST APPLICATIONS 
#
# TEST: GUPS
# ---------------------------------------

include ../Makefile.inc

SRC=./src

all: spmv
$(SRC)/execute_test.o: $(SRC)/execute_test.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(SRC)/shiftamt.o: $(SRC)/shiftamt.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(SRC)/spmv.o: $(SRC)/spmv.c
spmv: $(SRC)/spmv.o $(SRC)/shiftamt.o $(SRC)/execute_test.o
	$(CC) $(CFLAGS) -o $@ $(SRC)/spmv.o $(SRC)/shiftamt.o $(SRC)/execute_test.o $(LDFLAGS) $(LDLIBS)
clean: 
	rm -Rf ./spmv ./src/*.o
