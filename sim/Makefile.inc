#!/bin/sh

#----------------- MACROS
# -DGSIM_DEBUG : enable debug messages
# -DGSIM_TRACE : enable function tracing 

CC=gcc
CXX=g++
INC=-I./include/
CFLAGS=-O2 -Wall -g $(INC) -DGSIM_DEBUG
CXXFLAGS=-O2 -Wall -g $(INC) -DGSIM_DEBUG
LINK=-L./ -lgsim -L./hmc_sim -lhmcsim

AR=ar
AROPTS=rcs

LEX=flex
LEX_OPTS=-Pgsim
YACC=yacc

DOXYGEN=`which doxygen`
#-- EOF 
