ifdef DEBUG
  CXXFLAGS += -g -O0
else
  CXXFLAGS += -O2
  MACROS += NDEBUG
endif
ifdef SYNTAX_ONLY
  CXXFLAGS += -fsyntax-only
endif

CXXFLAGS += -std=c++0x -stdlib=libc++ -Wall -Wextra -pedantic -Werror

CPPFLAGS += $(foreach MACRO,$(MACROS),-D$(MACRO)) \\
            -I$(ROOTDIR)/include

LDFLAGS +=
