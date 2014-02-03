#!/bin/sh


#---------------------------------------------------------
# MACROS
#
#---------------------------------------------------------

#-- MEMSIM_TEST_MACROS
#-- MEMSIM TEST BUILD MACROS
MEMSIM_TEST_MACROS=

#-- CC
#-- C COMPILER
CC=gcc

#-- CXX
#-- C++ COMPILER
CXX=g++

#-- INC
#-- INCLUDE DIRECTORIES
INC=-I../../include/

#-- CFLAGS
#-- C COMPILER FLAGS
CFLAGS=-O2 -Wall -g $(INC) $(MEMSIM_TEST_MACROS)

#-- CXXFLAGS
#-- C++ COMPILER FLAGS
CXXFLAGS=-O2 -Wall -g $(INC) $(MEMSIM_TEST_MACROS)

#-- LDFLAGS
#-- LINKER OPTIONS
LDFLAGS=-L../../

#-- LDLIBS
#-- LIBRARIES FOR LINKING
LDLIBS=-lmemsim

#-- AR
#-- ARCHIVE BINARY
AR=ar

#-- AR_OPTS
#-- ARCHIVE OPTIONS
AR_OPTS=rcs

#-- DOXYGEN
#-- DOXYGEN BINARY
DOXYGEN=`which doxygen`

#-- EOF 
