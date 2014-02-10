#!/bin/sh
# 
# MEMSIM TEST MAKEFILE 
# 
# Drives building all the hmcsim tests


SUBDIRS :=	simple gups stream

CLEANDIRS :=	$(addsuffix .clean, $(SUBDIRS))

all:$(SUBDIRS)
$(SUBDIRS):
	@echo " Building $@"; $(MAKE) -C $@
.PHONY: all $(SUBDIRS) 

clean: $(CLEANDIRS) 
$(CLEANDIRS): 
	$(MAKE) -C $(basename $@) clean
.PHONY: clean $(CLEANDIRS)

