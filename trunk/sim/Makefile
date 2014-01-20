#!/bin/sh

include Makefile.inc

SRC=`pwd`/src

LIBOBJS=$(SRC)/gsim_opcodes.o $(SRC)/gsim_reg.o $(SRC)/gsim_mem.o $(SRC)/gsim_elf.o\
	$(SRC)/gsim_config.o $(SRC)/gsim_disass.o $(SRC)/gsim_inst_validate.o\
	$(SRC)/gsim_dump_inst.o $(SRC)/gsim_rand_reg.o $(SRC)/gsim_init_internals.o\
	$(SRC)/gsim_io.o $(SRC)/gsim_exec_functional.o $(SRC)/gsim_free_sim.o\
	$(SRC)/gsim_init_sim.o

GASMOBJS=$(SRC)/gasm_main.o $(SRC)/gasm_row.o $(SRC)/gasm_parser.o $(SRC)/gasm_io.o\
	$(SRC)/gasm_verify.o $(SRC)/gasm_asm.o

GSIMOBJS=$(SRC)/gsim_main.o $(SRC)/gsim_config.yy.o

all: libgsim.a libmemsim.a libhmcsim.a goblin-sim gasm
docs:
libhmcsim.a:
	make -C ./hmc_sim/
libmemsim.a:
	make -C ./mem_sim/
libgsim.a: 
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_init_sim.o $(SRC)/gsim_init_sim.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_free_sim.o $(SRC)/gsim_free_sim.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_dump_inst.o $(SRC)/gsim_dump_inst.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_opcodes.o $(SRC)/gsim_opcodes.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_rand_reg.o $(SRC)/gsim_rand_reg.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_io.o $(SRC)/gsim_io.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_reg.o $(SRC)/gsim_reg.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_mem.o $(SRC)/gsim_mem.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_elf.o $(SRC)/gsim_elf.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_config.o $(SRC)/gsim_config.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_disass.o $(SRC)/gsim_disass.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_init_internals.o $(SRC)/gsim_init_internals.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_inst_validate.o $(SRC)/gsim_inst_validate.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_exec_functional.o $(SRC)/gsim_exec_functional.c
	$(AR) $(AROPTS) $@ $(LIBOBJS)
gsim_config.yy.c: ./src/gsim_config_parser.lex
	$(LEX) $(LEX_OPTS) -o./src/$@ ./src/gsim_config_parser.lex
gsim_config.yy.o: gsim_config.yy.c
	$(CC) $(CFLAGS) -c -o ./src/$@ ./src/gsim_config.yy.c
goblin-sim: libgsim.a gsim_config.yy.o
	$(CC) $(CFLAGS) -c -o $(SRC)/gsim_main.o $(SRC)/gsim_main.c
	$(CC) $(CFLAGS) -o $@ $(GSIMOBJS) $(LINK)
gasm: libgsim.a
	$(CC) $(CFLAGS) -c -o $(SRC)/gasm_io.o $(SRC)/gasm_io.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gasm_verify.o $(SRC)/gasm_verify.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gasm_row.o $(SRC)/gasm_row.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gasm_parser.o $(SRC)/gasm_parser.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gasm_asm.o $(SRC)/gasm_asm.c
	$(CC) $(CFLAGS) -c -o $(SRC)/gasm_main.o $(SRC)/gasm_main.c
	$(CC) $(CFLAGS) -o $@ $(GASMOBJS) $(LINK)
check: 
	@echo "Executing GC64 Tests"; cd ./test/ && make check
clean: 
	rm -Rf ./src/*.o ./src/gsim_config.yy.c ./libgsim.a ./goblin-sim ./gasm
	make -C ./hmc_sim/ clean
	make -C ./mem_sim/ clean
