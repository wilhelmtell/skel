include $(ROOTDIR)/test/common.mk

LDFLAGS += -lboost_regex \
           -lboost_filesystem \
           -lboost_system \
           -lboost_program_options
OBJ = $(CURDIR)/main.o
DEPS = $(OBJ:.o=.dep)

.PHONY: check clean distclean tests

check:
	./test_skel

clean:
	rm -f $(OBJ) $(DEPS)

distclean: clean
	rm -f test_skel

test_skel: $(OBJ)
	$(LINK.cc) $(OUTPUT_OPTION) $^

%.dep: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<"

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "distclean"
  -include $(DEPS)
endif
endif

tests: test_skel
