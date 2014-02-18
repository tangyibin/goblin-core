#
# MEMSIM TOP-LEVEL MAKEFILE
# GOBLIN-CORE 64
#

include Makefile.inc
 
PKGS := ...
LIBNAME := memsim
SRCDIR := src
BUILDDIR := build
INC := -I./include/
LIBS :=
TARGET := lib$(LIBNAME).a
CFLAGS= -O2 -Wall -g $(INC)
LDFLAGS := 
ARFLAGS := rcs

.PHONY : test tools
 
SRCEXT = c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)
 
$(TARGET): $(OBJECTS)
	@echo " Linking..."; $(AR) $(ARFLAGS) $(TARGET) $(OBJECTS) 
 
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<
 
docs: 
	@echo " Building Docs..."; $(DOXYGEN) ./doxygen/mem_sim.cfg
doclean:
	@echo " Cleaning Docs..."; $(RM) -Rf ./doxygen/{html,latex,man,rtf,xml}
clean: doclean
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)
test: $(TARGET)
	@echo " Building Tests..."; make -C ./test/
tools:
	@echo " Building Tools..."; make -C ./tools/
toolsclean:
	@echo " Cleaning Tools..."; make -C ./tools/ clean
testclean:
	@echo " Cleaning Tests..."; make -C ./test/ clean
distclean: clean testclean doclean
 
-include $(DEPS)
 
.PHONY: clean
