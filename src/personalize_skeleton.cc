#include "personalize_skeleton.hh"
#include <boost/filesystem/path.hpp>
#include <fstream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <templog/logging.h>
#include "config.hh"
#include "error.hh"

namespace fs = boost::filesystem3;
namespace qi = boost::spirit::qi;
namespace phx= boost::phoenix;
namespace fsn= boost::fusion;

namespace {
struct substitution {
    substitution(std::map<std::string,std::string> const& subs)
    : subs(subs) { }

    template<typename>
    struct result { typedef bool type; };

    bool operator()(std::string& macro) const {
        auto pos = subs.find(macro);
        if( pos == subs.end() )
            macro = std::string("<<") + macro + ">>";
        else
            macro = pos->second;
        return true;
    }

private:
    std::map<std::string,std::string> const& subs;
};

template<typename In, typename Out>
struct skel_grammar : public qi::grammar<In> {
    struct fastfwd {
        template<typename, typename>
        struct result { typedef bool type; };

        template<typename R, typename O>
        bool operator()(R const& r, O& o) const {
            o = std::copy(r.begin(), r.end(), o);
            return true; // false to fail the parse
        }
    } copy;

    skel_grammar(Out& out, std::map<std::string,std::string> const& subs)
    : skel_grammar::base_type(start)
    , subs(subs)
    {
        using namespace qi;
        rawch = ('\\' >> char_) | char_;
        macro = ("<<" >> (
                          (*(rawch - ">>" - "<<") [ _val += _1 ])
                          % macro [ _val += _1 ] // allow nests
                         ) >>
                 ">>")
            [ _pass = phx::bind(substitution(subs), _val) ];

        start =
            raw [ +(rawch - "<<") ] [ _pass = phx::bind(copy, _1,
                                                        phx::ref(out)) ]
            % macro [ _pass = phx::bind(copy, _1,
                                        phx::ref(out)) ]
            ;

        BOOST_SPIRIT_DEBUG_NODE(start);
        BOOST_SPIRIT_DEBUG_NODE(macro);
# undef rawch
    }

private:
    qi::rule<In, char()> rawch;
    qi::rule<In, std::string()> macro;
    qi::rule<In> start;
    std::map<std::string,std::string> const& subs;
};
}

namespace skel {
void personalize_skeleton(fs::path const& in_path, fs::path const& out_path,
                          std::map<std::string,std::string> const& subs)
{
    typedef boost::spirit::multi_pass<std::istreambuf_iterator<char>> in_iter;
    typedef std::ostream_iterator<char> out_iter;

    std::ifstream in_file(in_path.string());
    in_iter b(in_file), e;
    std::ofstream out_file(out_path.string());
    out_iter out(out_file);

    skel_grammar<in_iter, out_iter> grammar(out, subs);
    TEMPLOG_LOG(skel::log_developer,templog::sev_debug,templog::aud_developer)
        << "expanding macros ...";
    if( ! qi::parse(b, e, grammar) )
        throw skeleton_syntax_error();
}
}  // namespace skel
