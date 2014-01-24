check_PROGRAMS = check_{APPNAME}
check_{APPNAME}_SOURCES = main.cc
check_{APPNAME}_CPPFLAGS = -I../include
check_{APPNAME}_LDADD = ../src/lib{APPNAME}.a
AM_CXXFLAGS = -std=c++11

check: check-am
	./$(check_PROGRAMS)
