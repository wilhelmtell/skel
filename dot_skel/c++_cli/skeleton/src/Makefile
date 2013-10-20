include $(ROOTDIR)/src/common.$(CXX).mk

# LDFLAGS += -lboost_filesystem
# if it's a static library we compile we might override PRODUCT:
# export PRODUCT = lib{APPNAME}.a
HDR := $(ROOTDIR)/src/verify_error.hh \\
       $(ROOTDIR)/src/verify.hh \\
       $(ROOTDIR)/src/verify.tcc \\
       $(ROOTDIR)/src/commandline.cc
SRC := $(ROOTDIR)/src/main.cc \\
       $(ROOTDIR)/src/verify_error.cc \\
       $(ROOTDIR)/src/commandline.cc
OBJ := $(foreach O,$(SRC:.cc=.o),$(CURDIR)/$(notdir $(O)))
DEPS := $(OBJ:.o=.dep)

.PHONY: all clean distclean install uninstall

# see the comment of the $(PRODUCT) rule of the root makefile
$(PRODUCT): $(OBJ)
	$(LINK.cc) $(OUTPUT_OPTION) $^
	@# TODO:if we compile a static library we might substitute the above with
	@# ar rcs $@ $^

all: $(PRODUCT)

clean:
	rm -f $(OBJ) $(DEPS) gmon.out

distclean: clean
	rm -f $(PRODUCT)

%.dep: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<" >"$@"

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "distclean"
ifneq "$(MAKECMDGOALS)" "uninstall"
  -include $(DEPS)
endif
endif
endif

install: all
	@# TODO:for a static library remember to s/bin/lib/ below
	mkdir --parents $(PREFIX)/bin/
	$(INSTALL) $(INSTALLFLAGS) $(PRODUCT) $(PREFIX)/bin/$(PRODUCT)
	@# TODO:for a static library we may also want to install headers
	@# mkdir --parents $(PREFIX)/include/{APPNAME}/
	@# $(INSTALL) $(INSTALLFLAGS) $(HDR) $(PREFIX)/include/{APPNAME}/

uninstall:
	@# TODO:if we compile a static library remember to s/bin/lib/ below
	rm -f $(PREFIX)/bin/$(PRODUCT)
	rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/bin/
	@# TODO:for a static library we may also want to uninstall headers
	@# rm -f $(foreach H,$(HDR),$(PREFIX)/include/{APPNAME}/$(H))
	@# rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/include/{APPNAME}/

