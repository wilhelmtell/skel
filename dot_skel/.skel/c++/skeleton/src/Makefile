include $(ROOTDIR)/src/conf.$(CXX).mk

# if it's a static library we compile we might override PRODUCT:
# export PRODUCT = lib{APPNAME}.a
PRODUCT := $(PROJECT)
HDR :=
SRC :=
OBJ := $(foreach O,$(SRC:.cc=.o),$(CURDIR)/$(notdir $(O)))
DEP := $(OBJ:.o=.dep)
MAINSRC := main.cc
MAINOBJ := $(CURDIR)/$(notdir $(MAINSRC:.cc=.o))
LDFLAGS += -L. -l$(PROJECT)

.PHONY: all clean distclean install uninstall

$(PRODUCT): lib$(PROJECT).a $(MAINOBJ)
	$(LINK.cc) $(OUTPUT_OPTION) $(MAINOBJ)

lib$(PROJECT).a: $(filter-out $(MAINOBJ),$(OBJ))
	ar rcs $@ $^

all: $(PRODUCT)

clean:
	rm -f $(OBJ) $(DEP) gmon.out

distclean: clean
	rm -f $(PRODUCT)

%.dep: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<" >"$@"

ifneq "$(MAKECMDGOALS)" "clean"
  ifneq "$(MAKECMDGOALS)" "distclean"
    ifneq "$(MAKECMDGOALS)" "uninstall"
      -include $(DEP)
    endif
  endif
endif

install: all
	mkdir --parents $(PREFIX)/bin/
	$(INSTALL) $(INSTALLFLAGS) $(PRODUCT) $(PREFIX)/bin/$(PRODUCT)
	@# mkdir --parents $(PREFIX)/lib/ $(PREFIX)/include/{APPNAME}/
	@# $(INSTALL) $(INSTALLFLAGS) lib$(PROJECT).a $(PREFIX)/lib/lib$(PROJECT).a
	@# $(INSTALL) $(INSTALLFLAGS) $(HDR) $(PREFIX)/include/{APPNAME}/

uninstall:
	rm -f $(PREFIX)/bin/$(PRODUCT)
	rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/bin/
	@# rm -f $(PREFIX)/lib/lib$(PROJECT).a
	@# rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/lib/
	@# rm -f $(foreach H,$(HDR),$(PREFIX)/include/{APPNAME}/$(H))
	@# rmdir --parents --ignore-fail-on-non-empty $(PREFIX)/include/{APPNAME}/
