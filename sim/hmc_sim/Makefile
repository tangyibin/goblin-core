#
# LIBPIM_COMP MAKEFILE
#
# Copyright (c) 2013 Micron Technology, Inc.
#

include Makefile.inc
 
PKGS := ...
LIBNAME := hmcsim
SRCDIR := src
BUILDDIR := build
INC := -I./include/
LIBS :=
TARGET := lib$(LIBNAME).a
CFLAGS= -O0 -g $(INC)
LDFLAGS := 
ARFLAGS := rcs

.PHONY : test tools
 
SRCEXT = c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)
 
$(TARGET): $(OBJECTS)
	@echo " Linking..."; $(AR) $(AR_OPTS) $(TARGET) $(OBJECTS) 
 
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<
 
docs: 
	@echo " Building Docs..."; $(DOXYGEN) ./doxygen/hmc_sim.cfg
doclean:
	@echo " Cleaning Docs..."; $(RM) -Rf ./doxygen/{html,latex,man,rtf,xml}
clean: doclean
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)
test: $(TARGET)
	make -C ./test/
tools:
	make -C ./tools/
toolsclean:
	make -C ./tools/ clean
testclean:
	make -C ./test/ clean
distclean: clean testclean doclean toolsclean
 
-include $(DEPS)
 
.PHONY: clean
