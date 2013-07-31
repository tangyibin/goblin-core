#!/bin/sh

CC=gcc
INC=-I./include/
CFLAGS=-O2 -Wall -g $(INC) 

AR=ar
AROPTS=rcs

SRC=`pwd`/src

LIBOBJS=$(SRC)/hmc_init.o $(SRC)/hmc_mem.o $(SRC)/hmc_config_devs.o\
	$(SRC)/hmc_links.o $(SRC)/hmc_trace.o $(SRC)/hmc_rqst.o 

all: libhmcsim.a
libhmcsim.a: 
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_init.o $(SRC)/hmc_init.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_mem.o $(SRC)/hmc_mem.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_trace.o $(SRC)/hmc_trace.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_links.o $(SRC)/hmc_links.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_rqst.o $(SRC)/hmc_rqst.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_config_devs.o $(SRC)/hmc_config_devs.c
	$(AR) $(AROPTS) $@ $(LIBOBJS)
clean:
	rm -Rf ./src/*.o ./libhmcsim.a
