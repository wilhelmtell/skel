include $(ROOTDIR)/src/conf.$(CXX).mk

MAINSRC := main.cc
LIBHDR :=

.PHONY: all clean distclean install uninstall

all:

clean:
	rm -f gmon.out

distclean: clean

install: all
	mkdir --parents $(PREFIX)/include/$(PROJECT)/
	$(INSTALL) $(INSTALLFLAGS) $(LIBHDR) $(PREFIX)/include/$(PROJECT)/

uninstall:
	rm -f $(foreach H,$(LIBHDR),$(PREFIX)/include/$(PROJECT)/$(H))
	rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/include/$(PROJECT)/
