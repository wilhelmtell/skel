include $(ROOTDIR)/src/common.mk

# if it's a static library we compile we might override PRODUCT:
# export PRODUCT = lib{APPNAME}.a
OBJ := $(CURDIR)/main.o
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
	@# TODO:if we compile a static library remember to s/bin/lib/ below
	install -s -D $(PRODUCT) $(PREFIX)/bin/$(PRODUCT)

uninstall:
	@# TODO:if we compile a static library remember to s/bin/lib/ below
	rm -f $(PREFIX)/bin/$(PRODUCT)
