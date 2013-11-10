#!/bin/bash

STREAM=../stream


BANKS=8
CAPACITY=2
LINKS=4
BSIZE=64
QDEPTH=64
XDEPTH=128
VAULTS=16
#NRQSTS=134217728
NRQSTS=33554432
#NRQSTS=4096
DRAMS=20
THREADS=16
SIMD=8

echo "Executing : $STREAM -b $BANKS -c $CAPACITY -l $LINKS -m $BSIZE -n 1 -q $QDEPTH -x $XDEPTH\
	-d $DRAMS -v $VAULTS -N $NRQSTS -T $THREADS -s $SIMD" 

$STREAM -b $BANKS -c $CAPACITY -l $LINKS -m $BSIZE -n 1 -q $QDEPTH -x $XDEPTH\
	-d $DRAMS -v $VAULTS -N $NRQSTS -T $THREADS -s $SIMD

