#!/bin/sh
# 
# MEMSIM TEST MAKEFILE 
# 
# Drives building all the hmcsim tests


SUBDIRS :=	simple 

CLEANDIRS :=	$(addsuffix .clean, $(SUBDIRS))

all:$(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@
.PHONY: all $(SUBDIRS) 

clean: $(CLEANDIRS) 
$(CLEANDIRS): 
	$(MAKE) -C $(basename $@) clean
.PHONY: clean $(CLEANDIRS)

