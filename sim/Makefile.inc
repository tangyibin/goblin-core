#!/bin/sh

CC=gcc
CXX=g++
INC=-I./include/
CFLAGS=-O2 -Wall -g $(INC)
CXXFLAGS=-O2 -Wall -g $(INC)
LINK=-L./ -lgsim

AR=ar
AROPTS=rcs

#-- EOF 
