include $(ROOTDIR)/src/conf.$(CXX).mk

EXE := $(PROJECT)
LIB := lib$(PROJECT).a
PRODUCT := $(EXE)
MAINSRC := main.cc
LIBHDR :=
LIBSRC := perform.cc
LDDIR := .
LDLIB := $(EXE)

MAINOBJ := $(CURDIR)/$(notdir $(MAINSRC:.cc=.o))
MAINDEP := $(MAINOBJ:.o=.dep)
LIBOBJ := $(foreach O,$(LIBSRC:.cc=.o),$(CURDIR)/$(notdir $(O)))
LIBDEP := $(LIBOBJ:.o=.dep)
LDFLAGS += $(foreach D,$(LDDIR),-L$D) \\
           $(foreach L,$(LDLIB),-l$L)

.PHONY: all clean distclean install uninstall

$(EXE): $(LIB) $(MAINOBJ)
	$(LINK.cc) $(OUTPUT_OPTION) $(MAINOBJ)

$(LIB): $(LIBOBJ)
	ar rcs $@ $^

all: $(PRODUCT)

clean:
	rm -f $(MAINOBJ) $(LIBOBJ) $(MAINDEP) $(LIBDEP) gmon.out

distclean: clean
	rm -f $(PRODUCT)

%.dep: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<" >"$@"

ifneq "$(MAKECMDGOALS)" "clean"
  ifneq "$(MAKECMDGOALS)" "distclean"
    ifneq "$(MAKECMDGOALS)" "uninstall"
      -include $(LIBDEP) $(MAINDEP)
    endif
  endif
endif

install: all
	mkdir --parents $(PREFIX)/bin/
	$(INSTALL_EXECUTABLE) $(PRODUCT) $(PREFIX)/bin/$(PRODUCT)

uninstall:
	rm -f $(PREFIX)/bin/$(PRODUCT)
	rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/bin/
