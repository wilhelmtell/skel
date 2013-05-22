include $(ROOTDIR)/src/conf.$(CXX).mk

EXE := $(PROJECT)
LIB := lib$(PROJECT).a
# PRODUCT = $(LIB)
PRODUCT := $(EXE)
MAINSRC := main.cc
LIBHDR :=
LIBSRC := perform.cc

MAINOBJ := $(CURDIR)/$(notdir $(MAINSRC:.cc=.o))
MAINDEP := $(MAINOBJ:.o=.dep)
LIBOBJ := $(foreach O,$(LIBSRC:.cc=.o),$(CURDIR)/$(notdir $(O)))
LIBDEP := $(LIBOBJ:.o=.dep)
LDFLAGS += -L. -l$(EXE)

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
	$(INSTALL) $(INSTALLFLAGS) $(PRODUCT) $(PREFIX)/bin/$(PRODUCT)
	@# mkdir --parents $(PREFIX)/lib/ $(PREFIX)/include/$(PROJECT)/
	@# $(INSTALL) $(INSTALLFLAGS) $(LIB) $(PREFIX)/lib/$(LIB)
	@# $(INSTALL) $(INSTALLFLAGS) $(LIBHDR) $(PREFIX)/include/$(PROJECT)/

uninstall:
	rm -f $(PREFIX)/bin/$(PRODUCT)
	rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/bin/
	@# rm -f $(PREFIX)/lib/$(LIB)
	@# rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/lib/
	@# rm -f $(foreach H,$(LIBHDR),$(PREFIX)/include/$(PROJECT)/$(H))
	@# rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/include/$(PROJECT)/
