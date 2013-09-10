#!/bin/sh

include Makefile.inc

WIKI=`which doxygen2gwiki`
WIKI_SRC=../../../goblin-core-wiki/

SRC=`pwd`/src

LIBOBJS=$(SRC)/hmc_init.o $(SRC)/hmc_mem.o $(SRC)/hmc_config_devs.o\
	$(SRC)/hmc_links.o $(SRC)/hmc_trace.o $(SRC)/hmc_rqst.o\
	$(SRC)/hmc_response.o $(SRC)/hmc_send.o $(SRC)/hmc_recv.o\
	$(SRC)/hmc_clock.o $(SRC)/hmc_jtag.o $(SRC)/hmc_reset.o

.PHONY : test

all: libhmcsim.a
wiki: docs
	$(WIKI) -s -d ./doxygen/xml -o $(WIKI_SRC) -p HMCSIM
docs:
	$(DOXYGEN) ./doxygen/hmc_sim.cfg
libhmcsim.a: 
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_init.o $(SRC)/hmc_init.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_mem.o $(SRC)/hmc_mem.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_send.o $(SRC)/hmc_send.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_recv.o $(SRC)/hmc_recv.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_trace.o $(SRC)/hmc_trace.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_links.o $(SRC)/hmc_links.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_rqst.o $(SRC)/hmc_rqst.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_response.o $(SRC)/hmc_response.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_config_devs.o $(SRC)/hmc_config_devs.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_clock.o $(SRC)/hmc_clock.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_jtag.o $(SRC)/hmc_jtag.c
	$(CC) $(CFLAGS) -c -o $(SRC)/hmc_reset.o $(SRC)/hmc_reset.c
	$(AR) $(AR_OPTS) $@ $(LIBOBJS)
doclean:
	rm -Rf ./doxygen/{html,latex,man,rtf,xml}
clean: doclean
	rm -Rf ./src/*.o ./libhmcsim.a
test: 
	make -C ./test/
