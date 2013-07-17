#!/bin/sh

include Makefile.inc

SRC=`pwd`/src

LIBOBJS=$(SRC)/gsim_opcodes.o $(SRC)/gsim_reg.o $(SRC)/gsim_mem.o $(SRC)/gsim_elf.o\
	$(SRC)/gsim_config.o $(SRC)/gsim_disass.o


all: libgsim.a goblin-sim
libgsim.a: 
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_opcodes.o $(SRC)/gsim_opcodes.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_reg.o $(SRC)/gsim_reg.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_mem.o $(SRC)/gsim_mem.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_elf.o $(SRC)/gsim_elf.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_config.o $(SRC)/gsim_config.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_disass.o $(SRC)/gsim_disass.c
	$(AR) $(AROPTS) $@ $(LIBOBJS)
gsim_config.yy.c: ./src/gsim_config_parser.lex
	$(LEX) $(LEX_OPTS) -o./src/$@ ./src/gsim_config_parser.lex
gsim_config.yy.o: gsim_config.yy.c
	$(CC) $(CFLAGS) -c -o ./src/$@ ./src/gsim_config.yy.c
goblin-sim: libgsim.a gsim_config.yy.o
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_main.o $(SRC)/gsim_main.c
	$(CC) $(CFLAGS) -o $@ $(SRC)/gsim_main.o $(SRC)/gsim_config.yy.o $(LINK)
clean: 
	rm -Rf ./src/*.o ./src/gsim_config.yy.c ./libgsim.a ./goblin-sim
