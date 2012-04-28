#include "helpers.hh"
#include <skel/application.hh>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <shell_word_split/shell_word_split.hh>

skel::application make_application(std::string const& cmdline_args)
{
    std::vector<std::string> split_args;
    sws::shell_word_split(cmdline_args.begin(), cmdline_args.end(),
                          std::back_inserter(split_args));
    std::vector<char const *> ptr_args;
    std::transform(split_args.begin(), split_args.end(),
                   std::back_inserter(ptr_args), [](std::string const& a) {
        return a.c_str();
    });
    return skel::application(ptr_args.size(), &ptr_args[0]);
}
