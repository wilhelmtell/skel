export ROOTDIR = $(realpath $(CURDIR))
ifndef PREFIX
  export PREFIX = /usr/local
endif

.PHONY: all clean distclean install uninstall dist help

all:
	${MAKE} --directory $(CURDIR)/src all

clean:
	${MAKE} --directory $(CURDIR)/src clean

distclean:
	${MAKE} --directory $(CURDIR)/src distclean
	rm -f skel_0.1.tar.gz

install:
	${MAKE} --directory $(CURDIR)/src install

uninstall:
	${MAKE} --directory $(CURDIR)/src uninstall

help:
	@echo " AVAILABLE TARGETS:"
	@echo
	@echo "all           (default)"
	@echo "dist                   "
	@echo "install                "
	@echo "uninstall              "
	@echo "clean                  "
	@echo "distclean              "
	@echo

dist:
	git archive --prefix=skel_0.1/ --format=tar.gz -9 HEAD >skel_0.1.tar.gz
