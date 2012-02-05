include $(ROOTDIR)/src/common.mk

LDFLAGS +=
OBJ = $(CURDIR)/main.o
DEPS = $(OBJ:.o=.d)

.PHONY: all clean distclean install uninstall

all: skel

clean:
	rm -f $(OBJ) $(DEPS) gmon.out

distclean: clean
	rm -f skel

skel: $(OBJ)
	$(LINK.cc) $(OUTPUT_OPTION) $^

%.d: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<"

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "distclean"
ifneq "$(MAKECMDGOALS)" "uninstall"
  -include $(DEPS)
endif
endif
endif

install: all
	install -s -D skel $(PREFIX)/bin/skel

uninstall:
	rm -f $(PREFIX)/bin/skel
