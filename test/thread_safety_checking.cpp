// Copyright Antony Polukhin, 2016-2017.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/stacktrace/stacktrace_fwd.hpp>

#include <boost/stacktrace.hpp>
#include <boost/thread.hpp>
#include <boost/optional.hpp>
#include <boost/core/lightweight_test.hpp>

#ifdef BOOST_STACKTRACE_DYN_LINK
#   define BOOST_ST_API BOOST_SYMBOL_IMPORT
#else
#   define BOOST_ST_API
#endif

using boost::stacktrace::stacktrace;

typedef std::pair<stacktrace, stacktrace> (*foo1_t)(int i);
BOOST_ST_API std::pair<stacktrace, stacktrace> foo2(int i, foo1_t foo1);
BOOST_ST_API stacktrace return_from_nested_namespaces();

BOOST_NOINLINE std::pair<stacktrace, stacktrace> foo1(int i) {
    if (i) {
        return foo2(i - 1, foo1);
    }

    std::pair<stacktrace, stacktrace> ret;
    try {
        throw std::logic_error("test");
    } catch (const std::logic_error& /*e*/) {
        ret.second = stacktrace();
        return ret;
    }
}

void main_test_loop() {
    std::size_t loops = 100;
    std::size_t Depth = 21;

    boost::optional<std::pair<stacktrace, stacktrace> > ethalon;

    while (--loops) {
        std::pair<stacktrace, stacktrace> res = foo2(Depth, foo1);
        if (ethalon) {
            BOOST_TEST(res == *ethalon);
        } else {
            ethalon = res;
        }
    }
}

int main() {
    boost::thread t1(main_test_loop);
    boost::thread t2(main_test_loop);
    boost::thread t3(main_test_loop);
    main_test_loop();

    t1.join();
    t2.join();
    t3.join();

    return boost::report_errors();
}