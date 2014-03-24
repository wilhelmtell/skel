bin_PROGRAMS = skel
skel_SOURCES = main.cc
skel_CPPFLAGS = -I../include
skel_LDADD = -L../src \
             -lskel \
             -lboost_filesystem \
             -lboost_system \
             -lboost_regex \
             -lboost_program_options
AM_CXXFLAGS = -std=c++11

noinst_LIBRARIES = libskel.a
libskel_a_SOURCES = application.hh application.cc \
                    token.hh \
                    scanner.hh scanner.cc \
                    parser.hh parser.cc \
                    parser_error.hh \
                    copy_part.hh copy_part.cc \
                    instantiate_part.hh instantiate_part.cc \
                    instantiate_parts.hh instantiate_parts.cc \
                    instantiate_skeleton.hh instantiate_skeleton.cc \
                    skeleton_instantiation_error.hh \
                    mapping.hh mapping.cc \
                    mv.hh mv.cc \
                    print_message.hh print_message.cc \
                    rename_files.hh rename_files.cc \
                    renames_atom.hh renames_atom.tcc renames_atom.cc \
                    session.hh session.cc \
                    invalid_user_interface_input.hh \
                    command.hh \
                    memory.hh
