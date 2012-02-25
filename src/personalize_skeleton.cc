#include "personalize_skeleton.hh"
#include <boost/filesystem/path.hpp>
#include <fstream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <string>
#include <algorithm>
#include <iterator>

namespace fs = boost::filesystem3;
namespace qi = boost::spirit::qi;
namespace phx= boost::phoenix;
namespace fsn= boost::fusion;

namespace {
#define SUPPORT_ESCAPES

static bool process(std::string& macro)
{
    if( macro == "error" ) {
        return false; // fail the parse
    } else if( macro == "hello" ) {
        macro = "bye";
    } else if( macro == "bye" ) {
        macro = "We meet again";
    } else if( macro == "sideeffect" ) {
        std::cerr << "this is a side effect while parsing\n";
        macro = "(done)";
    } else if( std::string::npos != macro.find('~') ) {
        std::reverse(macro.begin(), macro.end());
        macro.erase(std::remove(macro.begin(), macro.end(), '~'));
    } else {
        macro = std::string("<<") + macro + ">>"; // this makes the unsupported macros appear unchanged
    }
    return true;
}

template<typename In, typename Out>
struct skel_grammar : public qi::grammar<In> {
    struct fastfwd {
        template<typename, typename>
        struct result { typedef bool type; };

        template<typename R, typename O>
        bool operator()(R const& r, O& o) const {
#ifndef SUPPORT_ESCAPES
            o = std::copy(r.begin(), r.end(), o);
#else
            auto b = std::begin(r), e = std::end(r);
            while( b != e ) {
                if( '\\' == *b && e == ++b )
                    break;
                *o++ = *b++;
            }
#endif
            return true; // false to fail the parse
        }
    } copy;

    skel_grammar(Out& out) : skel_grammar::base_type(start)
    {
        using namespace qi;

#ifdef SUPPORT_ESCAPES
        rawch = ('\\' >> char_) | char_;
#else
# define rawch qi::char_
#endif

        macro = ("<<" >> (
                          (*(rawch - ">>" - "<<") [ _val += _1 ])
                          % macro [ _val += _1 ] // allow nests
                         ) >>
                 ">>")
            [ _pass = phx::bind(process, _val) ];

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
#ifdef SUPPORT_ESCAPES
    qi::rule<In, char()> rawch;
#endif
    qi::rule<In, std::string()> macro;
    qi::rule<In> start;
};
}

namespace skel {
void personalize_skeleton(fs::path const& in_path, fs::path const& out_path)
{
    typedef boost::spirit::multi_pass<std::istreambuf_iterator<char>> in_iter;
    typedef std::ostream_iterator<char> out_iter;

    std::ifstream in_file(in_path.string());
    in_iter b(in_file), e;
    std::ofstream out_file(out_path.string());
    out_iter out(out_file);

    skel_grammar<in_iter, out_iter> grammar(out);
    /* bool r = */ qi::parse(b, e, grammar);
}
}  // namespace skel
