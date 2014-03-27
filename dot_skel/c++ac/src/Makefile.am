bin_PROGRAMS = {APPNAME}
{APPNAME}_SOURCES = main.cc
{APPNAME}_CPPFLAGS = -I../include
{APPNAME}_LDADD = -L. \\
                  -l{APPNAME}
AM_CXXFLAGS = -std=c++11

noinst_LIBRARIES = lib{APPNAME}.a
lib{APPNAME}_a_SOURCES = dummy.cc dummy.hh
