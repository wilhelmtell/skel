export PRODUCT := {APPNAME}
export VERSION := {VERSION}
export ROOTDIR := $(realpath $(CURDIR))
ifndef PREFIX
  export PREFIX := /usr/local
endif

.PHONY: $(PRODUCT) all clean distclean check tests install uninstall dist help

check: tests
	${MAKE} --directory $(ROOTDIR)/test check

# here we assume the default rule of each of our child makefiles is the
# $(PRODUCT) rule. this allows us to refer to each child $(PRODUCT) rule with
# "make". in contrast, "make $(PRODUCT)" would't work if any child makefile
# redefines $(PRODUCT).
$(PRODUCT):
	${MAKE} --directory $(ROOTDIR)/src

all:
	${MAKE} --directory $(ROOTDIR)/src all
	${MAKE} --directory $(ROOTDIR)/test all

clean:
	${MAKE} --directory $(ROOTDIR)/test clean
	${MAKE} --directory $(ROOTDIR)/src clean

distclean:
	${MAKE} --directory $(ROOTDIR)/test distclean
	${MAKE} --directory $(ROOTDIR)/src distclean
	rm -f $(PRODUCT)_$(VERSION).tar.gz

tests: $(PRODUCT)
	${MAKE} --directory $(ROOTDIR)/test tests

install:
	${MAKE} --directory $(ROOTDIR)/src install

uninstall:
	${MAKE} --directory $(ROOTDIR)/src uninstall

help:
	@echo " AVAILABLE TARGETS:"
	@echo
	@echo "$(PRODUCT)"
	@echo "all                    "
	@echo "dist                   "
	@echo "check         (default)"
	@echo "install                "
	@echo "uninstall              "
	@echo "clean                  "
	@echo "distclean              "
	@echo

dist:
	git archive --prefix=$(PRODUCT)_$(VERSION)/ --format=tar.gz -9 HEAD >$(PRODUCT)_$(VERSION).tar.gz
