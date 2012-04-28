#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <boost/filesystem.hpp>
#include <skel/application.hh>
#include <catch_fixtures/pushd_temporary_directory.hh>
#include "helpers.hh"

namespace fs = boost::filesystem;

TEST_CASE("rollback on error", "rollback on error as if skel never ran") {
    fixtures::pushd_temporary_directory temp_dir;
    make_application("--skeleton c++").exec();
}
