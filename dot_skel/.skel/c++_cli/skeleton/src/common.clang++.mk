ifdef DEBUG
  CXXFLAGS += -g -O0
else
  CXXFLAGS += -O2
  LIBRARY_INSTALL_FLAGS += --strip
  EXECUTABLE_INSTALL_FLAGS += --strip
  MACROS += NDEBUG
endif
ifdef SYNTAX_ONLY
  CXXFLAGS += -fsyntax-only
endif
HEADER_INSTALL_FLAGS += --mode=0644

CXXFLAGS += -std=c++0x -stdlib=libc++ -Wall -Wextra -pedantic -Werror

CPPFLAGS += $(foreach MACRO,$(MACROS),-D$(MACRO)) \\
            -I$(ROOTDIR)/include

LDFLAGS +=

INSTALL ?= install
HEADER_INSTALL = $(INSTALL) $(HEADER_INSTALL_FLAGS)
LIBRARY_INSTALL = $(INSTALL) $(LIBRARY_INSTALL_FLAGS)
EXECUTABLE_INSTALL = $(INSTALL) $(EXECUTABLE_INSTALL_FLAGS)
