include $(ROOTDIR)/src/conf.$(CXX).mk

EXE := $(PROJECT)
LIB := lib$(PROJECT).a
PRODUCT := $(EXE)
MAINSRC := main.cc
LIBHDR := application.hh \
          command.hh \
          copy_part.hh \
          instantiate_part.hh \
          instantiate_parts.hh \
          instantiate_skeleton.hh \
          invalid_user_interface_input.hh \
          mapping.hh \
          memory.hh \
          mv.hh \
          parser.hh \
          parser_error.hh \
          print_message.hh \
          rename_files.hh \
          renames_atom.hh \
          renames_atom.tcc \
          scanner.hh \
          session.hh \
          skeleton_instantiation_error.hh \
          token.hh
LIBSRC := application.cc \
          copy_part.cc \
          instantiate_part.cc \
          instantiate_parts.cc \
          instantiate_skeleton.cc \
          mapping.cc \
          mv.cc \
          parser.cc \
          print_message.cc \
          rename_files.cc \
          renames_atom.cc \
          scanner.cc \
          session.cc

MAINOBJ := $(CURDIR)/$(notdir $(MAINSRC:.cc=.o))
MAINDEP := $(MAINOBJ:.o=.dep)
LIBOBJ := $(foreach O,$(LIBSRC:.cc=.o),$(CURDIR)/$(notdir $(O)))
LIBDEP := $(LIBOBJ:.o=.dep)
LDDIR := .
LDLIB := $(EXE) \
         boost_filesystem \
         boost_system \
         boost_regex \
         boost_program_options
LDFLAGS += $(foreach D,$(LDDIR),-L$D) \
           $(foreach L,$(LDLIB),-l$L)

.PHONY: all clean distclean install uninstall

$(EXE): $(LIB) $(MAINOBJ)
	$(LINK.cc) $(OUTPUT_OPTION) $(MAINOBJ)

$(LIB): $(LIBOBJ)
	ar rcs $@ $^

all: $(PRODUCT)

clean:
	rm -f $(MAINOBJ) $(LIBOBJ) $(MAINDEP) $(LIBDEP) gmon.out

distclean: clean
	rm -f $(PRODUCT)

%.dep: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<" >"$@"

ifneq "$(MAKECMDGOALS)" "clean"
  ifneq "$(MAKECMDGOALS)" "distclean"
    ifneq "$(MAKECMDGOALS)" "uninstall"
      -include $(LIBDEP) $(MAINDEP)
    endif
  endif
endif

install: all
	mkdir --parents $(PREFIX)/bin/
	$(INSTALL) $(PRODUCT) $(PREFIX)/bin/$(PRODUCT)

uninstall:
	rm -f $(PREFIX)/bin/$(PRODUCT)
	rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/bin/
