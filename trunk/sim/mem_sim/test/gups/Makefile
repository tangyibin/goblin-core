#!/bin/sh
#
# MEMSIM TEST APPLICATIONS
#
# TEST: GUPS
# ------------------------------------------

include ../Makefile.inc

SRC=./src
OBJS=$(SRC)/gups.o $(SRC)/execute_test.o

all: gups
gups:
	@echo " Building $(SRC)/execute_test.c"; $(CC) $(CFLAGS) -c -o $(SRC)/execute_test.o $(SRC)/execute_test.c 
	@echo " Building $(SRC)/gups.c"; $(CC) $(CFLAGS) -c -o $(SRC)/gups.o $(SRC)/gups.c 
	@echo " Linking $@"; $(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS) 
clean:
	rm -Rf ./gups ./src/*.o
