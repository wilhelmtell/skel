include $(ROOTDIR)/test/common.mk

LDFLAGS += -lboost_regex \
           -lboost_filesystem \
           -lboost_system \
           -lboost_program_options
OBJ = $(CURDIR)/main.o \
      $(CURDIR)/helpers.o \
      $(ROOTDIR)/src/mapping.o \
      $(ROOTDIR)/src/mv.o \
      $(ROOTDIR)/src/renames_atom.o \
      $(ROOTDIR)/src/rename_files.o \
      $(ROOTDIR)/src/scanner.o \
      $(ROOTDIR)/src/parser.o \
      $(ROOTDIR)/src/copy_part.o \
      $(ROOTDIR)/src/instantiate_part.o \
      $(ROOTDIR)/src/instantiate_parts.o \
      $(ROOTDIR)/src/instantiate_skeleton.o \
      $(ROOTDIR)/src/print_message.o \
      $(ROOTDIR)/src/session.o \
      $(ROOTDIR)/src/application.o
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
