#!/bin/sh


#---------------------------------------------------------
# MACROS
#
# Each of the following can be added to the MEMSIM_MACROS
#     option below in order to enable/disable certain
#     options.
# 
#---------------------------------------------------------

#-- MEMSIM_MACROS
#-- MEMSIM BUILD MACROS
MEMSIM_MACROS=

#-- CC
#-- C COMPILER
CC=gcc

#-- CXX
#-- C++ COMPILER
CXX=g++

#-- INC
#-- INCLUDE DIRECTORIES
INC=-I./include/

#-- CFLAGS
#-- C COMPILER FLAGS
CFLAGS=-O2 -Wall -g $(INC) $(MEMSIM_MACROS)

#-- CXXFLAGS
#-- C++ COMPILER FLAGS
CXXFLAGS=-O2 -Wall -g $(INC) $(MEMSIM_MACROS)

#-- AR
#-- ARCHIVE BINARY
AR=ar

#-- AR_OPTS
#-- ARCHIVE OPTIONS
ARFLAGS=rcs

#-- DOXYGEN
#-- DOXYGEN BINARY
DOXYGEN=`which doxygen`

#-- EOF 
