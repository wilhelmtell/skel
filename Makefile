export PROJECT := skel
export EXE := $(PROJECT)
export LIB := lib$(PROJECT).a
export VERSION := $(shell git describe --dirty --always 2>/dev/null || echo 0)
export ROOTDIR := $(realpath $(CURDIR))

include $(ROOTDIR)/conf.mk

.PHONY: all clean distclean check install uninstall dist help

all:
	${MAKE} --directory $(ROOTDIR)/src all
	${MAKE} --directory $(ROOTDIR)/test all

check: $(LIB)
	${MAKE} --directory $(ROOTDIR)/test check

$(EXE):
	${MAKE} --directory $(ROOTDIR)/src $(EXE)

$(LIB):
	${MAKE} --directory $(ROOTDIR)/src $(LIB)

clean:
	${MAKE} --directory $(ROOTDIR)/test clean
	${MAKE} --directory $(ROOTDIR)/src clean

distclean:
	${MAKE} --directory $(ROOTDIR)/test distclean
	${MAKE} --directory $(ROOTDIR)/src distclean
	rm -f $(PROJECT)_$(VERSION).tar.gz

install:
	${MAKE} --directory $(ROOTDIR)/src install

uninstall:
	${MAKE} --directory $(ROOTDIR)/src uninstall

help:
	@echo " AVAILABLE TARGETS:"
	@echo
	@echo "all           (default)"
	@echo "dist                   "
	@echo "check                  "
	@echo "install                "
	@echo "uninstall              "
	@echo "clean                  "
	@echo "distclean              "
	@echo "$(EXE)"
	@echo "$(LIB)"
	@echo

dist:
	git archive --prefix=$(PROJECT)_$(VERSION)/ --format=tar.gz -9 HEAD >$(PROJECT)_$(VERSION).tar.gz
