include $(ROOTDIR)/src/conf.$(CXX).mk

LIBBASE := $(PROJECT)
LIB := lib$(LIBBASE).a
PRODUCT = $(LIB)
LIBHDR :=
LIBSRC := perform.cc

LIBOBJ := $(foreach O,$(LIBSRC:.cc=.o),$(CURDIR)/$(notdir $(O)))
LIBDEP := $(LIBOBJ:.o=.dep)

.PHONY: all clean distclean install uninstall

$(LIB): $(LIBOBJ)
	ar rcs $@ $^

all: $(PRODUCT)

clean:
	rm -f $(LIBOBJ) $(LIBDEP) gmon.out

distclean: clean
	rm -f $(PRODUCT)

%.dep: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<" >"$@"

ifneq "$(MAKECMDGOALS)" "clean"
  ifneq "$(MAKECMDGOALS)" "distclean"
    ifneq "$(MAKECMDGOALS)" "uninstall"
      -include $(LIBDEP)
    endif
  endif
endif

install: all
	mkdir --parents $(PREFIX)/lib/ $(PREFIX)/include/$(PROJECT)/
	$(INSTALL_LIBRARY) $(LIB) $(PREFIX)/lib/$(LIB)
	$(INSTALL_HEADER) $(LIBHDR) $(PREFIX)/include/$(PROJECT)/

uninstall:
	rm -f $(PREFIX)/lib/$(LIB)
	rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/lib/
	rm -f $(foreach H,$(LIBHDR),$(PREFIX)/include/$(PROJECT)/$(H))
	rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/include/$(PROJECT)/
