#!/bin/sh

all:
	@for a in $$(ls) ; do \
		if [ -d $$a ]; then \
			echo "processing test folder $$a"; \
			$(MAKE) -C $$a; \
		fi; \
	done; \
	echo "Done!"
clean:
	@for a in $$(ls) ; do \
		if [ -d $$a ]; then \
			echo "cleaning test folder $$a"; \
			$(MAKE) -C $$a clean; \
		fi; \
	done; \
	echo "Done!"
