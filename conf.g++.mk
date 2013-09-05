include $(ROOTDIR)/conf.mk

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
ifdef EXTRA_WARNINGS
  CXXFLAGS += -Wctor-dtor-privacy -Wnoexcept -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wdouble-promotion -Wformat=2 -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wsync-nand -Wuninitialized -Wunknown-pragmas -Wtrampolines -Wfloat-equal -Wundef -Wshadow -Wunsafe-loop-optimizations -Wc++11-compat -Wcast-qual -Wcast-align -Wconversion -Wzero-as-null-pointer-constant -Wsign-conversion -Wlogical-op -Waggregate-return -Wmissing-declarations -Wpadded -Wredundant-decls -Wdisabled-optimization -Weffc++ -Wpointer-arith -Wunreachable-code -Winline
endif
INCLUDE_SEARCH_PATHS += $(ROOTDIR)/include

SYSTEM_INCLUDE_SEARCH_PATHS +=

HEADER_INSTALL_FLAGS += --mode=0644

CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -Werror

CPPFLAGS += $(foreach MACRO,$(MACROS),-D$(MACRO)) \
            $(foreach D,$(INCLUDE_SEARCH_PATHS),-I$D) \
            $(foreach D,$(SYSTEM_INCLUDE_SEARCH_PATHS),-isystem$D)

LDFLAGS +=

INSTALL ?= install
HEADER_INSTALL = $(INSTALL) $(HEADER_INSTALL_FLAGS)
LIBRARY_INSTALL = $(INSTALL) $(LIBRARY_INSTALL_FLAGS)
EXECUTABLE_INSTALL = $(INSTALL) $(EXECUTABLE_INSTALL_FLAGS)
