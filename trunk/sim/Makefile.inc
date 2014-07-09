#!/bin/sh

#----------------- MACROS
# -DGSIM_DEBUG : enable debug messages
# -DGSIM_TRACE : enable function tracing 

CC=gcc
CXX=g++
INC=-I./include/ -I./hmc_sim/include/ -I./mem_sim/include/
CFLAGS=-O2 -Wall -g $(INC) -DGSIM_DEBUG -DGSIM_TRACE -fopenmp
CXXFLAGS=-O2 -Wall -g $(INC) -DGSIM_DEBUG -fopenmp
LINK=-L./ -lgsim -L./hmc_sim -lhmcsim -L./mem_sim -lmemsim

AR=ar
ARFLAGS=rcs

LEX=flex
LEX_OPTS=-Pgsim
YACC=yacc

DOXYGEN=`which doxygen`
#-- EOF 
