include $(ROOTDIR)/test/conf.$(CXX).mk

PRODUCT = test_$(PROJECT)
HDR :=
SRC :=
LDDIR :=
LDLIB :=

MAINSRC := main.cc
MAINOBJ := $(CURDIR)/$(notdir $(MAINSRC:.cc=.o))
MAINDEP := $(MAINOBJ:.o=.dep)
OBJ := $(foreach O,$(SRC:.cc=.o),$(CURDIR)/$(O))
DEP := $(OBJ:.o=.dep)
LDFLAGS += $(foreach D,$(LDDIR),-L$D) \\
           $(foreach L,$(LDLIB),-l$L)

.PHONY: check clean distclean

$(PRODUCT): $(OBJ) $(MAINOBJ)
	$(LINK.cc) $(OUTPUT_OPTION) $^

check: $(PRODUCT)
	./$(PRODUCT)

all: check

clean:
	rm -f $(MAINOBJ) $(OBJ) $(MAINDEP) $(DEP)

distclean: clean
	rm -f $(PRODUCT)

%.dep: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<" >"$@"

ifneq "$(MAKECMDGOALS)" "clean"
  ifneq "$(MAKECMDGOALS)" "distclean"
    -include $(MAINDEP) $(DEP)
  endif
endif
