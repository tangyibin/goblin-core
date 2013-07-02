#!/bin/sh

include Makefile.inc

SRC=`pwd`/src

LIBOBJS=$(SRC)/gsim_opcodes.o $(SRC)/gsim_reg.o $(SRC)/gsim_mem.o $(SRC)/gsim_elf.o\
	$(SRC)/gsim_config.o


all: libgsim.a goblin-sim
libgsim.a:
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_opcodes.o $(SRC)/gsim_opcodes.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_reg.o $(SRC)/gsim_reg.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_mem.o $(SRC)/gsim_mem.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_elf.o $(SRC)/gsim_elf.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_config.o $(SRC)/gsim_config.c
	$(AR) $(AROPTS) $@ $(LIBOBJS)
goblin-sim: libgsim.a
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_main.o $(SRC)/gsim_main.c
	$(CC) $(CFLAGS) -o $@ $(SRC)/gsim_main.o $(LINK)
clean: 
	rm -Rf ./src/*.o ./libgsim.a ./goblin-sim
