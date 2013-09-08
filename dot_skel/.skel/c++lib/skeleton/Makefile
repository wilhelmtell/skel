export PROJECT := {APPNAME}
export LIB := lib$(PROJECT).a
export VERSION := {VERSION}
export ROOTDIR := $(realpath $(CURDIR))

include $(ROOTDIR)/conf.mk

.PHONY: all clean distclean check install uninstall dist help

check: $(LIB)
	$\{MAKE\} --directory $(ROOTDIR)/test check

$(LIB):
	$\{MAKE\} --directory $(ROOTDIR)/src $(LIB)

all:
	$\{MAKE\} --directory $(ROOTDIR)/src all
	$\{MAKE\} --directory $(ROOTDIR)/test all

clean:
	$\{MAKE\} --directory $(ROOTDIR)/test clean
	$\{MAKE\} --directory $(ROOTDIR)/src clean

distclean:
	$\{MAKE\} --directory $(ROOTDIR)/test distclean
	$\{MAKE\} --directory $(ROOTDIR)/src distclean
	rm -f $(PROJECT)_$(VERSION).tar.gz

install:
	$\{MAKE\} --directory $(ROOTDIR)/src install

uninstall:
	$\{MAKE\} --directory $(ROOTDIR)/src uninstall

help:
	@echo " AVAILABLE TARGETS:"
	@echo
	@echo "$(LIB)"
	@echo "all                    "
	@echo "dist                   "
	@echo "check         (default)"
	@echo "install                "
	@echo "uninstall              "
	@echo "clean                  "
	@echo "distclean              "
	@echo

dist:
	git archive --prefix=$(PROJECT)_$(VERSION)/ --format=tar.gz -9 HEAD >$(PROJECT)_$(VERSION).tar.gz
