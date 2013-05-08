include $(ROOTDIR)/test/common.$(CXX).mk

export PRODUCT = test_{APPNAME}
HDR :=
SRC := main.cc
OBJ := $(foreach O,$(SRC:.cc=.o),$(CURDIR)/$(O))
DEPS := $(OBJ:.o=.dep)

.PHONY: check clean distclean

# LDFLAGS+=-lboost_filesystem
# see the comment of the $(PRODUCT) rule of the root makefile
$(PRODUCT): $(OBJ)
	$(LINK.cc) $(OUTPUT_OPTION) $^

check: $(PRODUCT)
	./$(PRODUCT)

all: check

clean:
	rm -f $(OBJ) $(DEPS)

distclean: clean
	rm -f $(PRODUCT)

%.dep: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<" >"$@"

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "distclean"
  -include $(DEPS)
endif
endif
