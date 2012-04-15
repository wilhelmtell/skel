export ROOTDIR = $(realpath $(CURDIR))
include $(ROOTDIR)/conf.mk

.PHONY: all check clean distclean install uninstall dist help

all:
	${MAKE} --directory $(CURDIR)/src all

check: tests
	${MAKE} --directory $(CURDIR)/test check

tests: all
	${MAKE} --directory $(CURDIR)/test tests

clean:
	${MAKE} --directory $(CURDIR)/test clean
	${MAKE} --directory $(CURDIR)/src clean

distclean:
	${MAKE} --directory $(CURDIR)/test distclean
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
	@echo "check                  "
	@echo "dist                   "
	@echo "install                "
	@echo "uninstall              "
	@echo "clean                  "
	@echo "distclean              "
	@echo

dist:
	git archive --prefix=skel_0.1/ --format=tar.gz -9 HEAD >skel_0.1.tar.gz
