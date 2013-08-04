#!/bin/sh

CC=gcc
INC=-I../../include/
CFLAGS=-O2 -Wall -g $(INC) 
LIBS=-L../../ -lhmcsim

SRC=`pwd`/src

OBJS=$(SRC)/physrand_main.o

all: hmc_physrand
hmc_physrand:
	$(CC) $(CFLAGS) -c -o $(SRC)/physrand_main.o $(SRC)/physrand_main.c
	$(CC) $(CFLAGS) -o hmc_physrand $(OBJS) $(LIBS)
clean:
	rm -Rf ./src/*.o ./hmc_physrand
