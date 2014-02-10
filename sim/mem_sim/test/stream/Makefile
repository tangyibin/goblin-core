#!/bin/sh
#
# MEMSIM TEST APPLICATIONS
#
# TEST: STREAM
# ------------------------------------------

include ../Makefile.inc

SRC=./src
OBJS=$(SRC)/stream.o $(SRC)/execute_test.o

all: stream
stream:
	@echo " Building $(SRC)/execute_test.c"; $(CC) $(CFLAGS) -c -o $(SRC)/execute_test.o $(SRC)/execute_test.c 
	@echo " Building $(SRC)/stream.c"; $(CC) $(CFLAGS) -c -o $(SRC)/stream.o $(SRC)/stream.c 
	@echo " Linking $@"; $(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS) 
clean:
	rm -Rf ./stream ./src/*.o
