check_PROGRAMS = check_{APPNAME}
check_{APPNAME}_SOURCES = dummy.cc main.cc
check_{APPNAME}_CPPFLAGS = -I../include
check_{APPNAME}_LDADD = -L../src \\
                        -l{APPNAME}
AM_CXXFLAGS = -std=c++11

check: check-am
	./$(check_PROGRAMS)
