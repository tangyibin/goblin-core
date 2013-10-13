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
LDFLAGS := 
ARFLAGS := rcs

.PHONY : test
 
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
testclean:
	make -C ./test/ clean
distclean: clean testclean doclean
 
-include $(DEPS)
 
.PHONY: clean
