check_PROGRAMS = check_skel
check_skel_SOURCES = helpers.cc helpers.hh main.cc
check_skel_CPPFLAGS = -I../include
check_skel_LDADD = -L../src \
                   -lskel \
                   -lboost_filesystem \
                   -lboost_system \
                   -lboost_regex \
                   -lboost_program_options
AM_CXXFLAGS = -std=c++11

check: check-am
	./$(check_PROGRAMS)
