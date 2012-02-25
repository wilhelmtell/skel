ifdef DEBUG
  CXXFLAGS += -g -O0
else
  CXXFLAGS += -O2
  MACROS += NDEBUG
endif

ifdef SYNTAX_ONLY
  CXXFLAGS += -fsyntax-only
endif

ifdef EXTRA_WARNINGS
  CXXFLAGS += -Weffc++ \
              -Wfloat-equal \
              -Wshadow \
              -Wunsafe-loop-optimizations \
              -Wpointer-arith \
              -Wc++-compat \
              -Wcast-qual \
              -Wcast-align \
              -Wconversion \
              -Wshorten-64-to-32 \
              -Wpadded \
              -Wredundant-decls \
              -Wunreachable-code \
              -Winline
endif

CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -Werror

CPPFLAGS += $(foreach MACRO,$(MACROS),-D$(MACRO)) \
            -I$(ROOTDIR)/include
