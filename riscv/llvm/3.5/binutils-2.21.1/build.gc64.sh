#!/bin/bash

srcdir := $(shell cd @top_srcdir@ && pwd)

BUILD_DIR=./build.gc64
INSTALL_DIR=$HOME/riscv/
OPTIONS="--target=riscv-linux \
		--prefix=$(INSTALL_DIR) \
		--enable-tls \
		--enable-languages=c \
		--with-newlib \
		--disable-multilib"

#-- clean the old build 
rm -Rf $BUILD_DIR

#-- create a new directory 
mkdir $BUILD_DIR

#-- cd and configure
cd $BUILD_DIR && $srcdir/$BUILD_DIR/configure $OPTIONS
cd $BUILD_DIR && make -f $srcdir/$BUILD_DIR/makefile

#-- EOF 
