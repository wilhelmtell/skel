include $(ROOTDIR)/test/common.mk

export PRODUCT = test_{APPNAME}
OBJ := $(CURDIR)/main.o
DEPS := $(OBJ:.o=.dep)

.PHONY: check clean distclean tests

# see the comment of the $(PRODUCT) rule of the root makefile
$(PRODUCT): $(OBJ)
	$(LINK.cc) $(OUTPUT_OPTION) $^

check: tests
	./$(PRODUCT)

all: check

clean:
	rm -f $(OBJ) $(DEPS)

distclean: clean
	rm -f $(PRODUCT)

%.dep: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<"

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "distclean"
  -include $(DEPS)
endif
endif

tests: $(PRODUCT)
