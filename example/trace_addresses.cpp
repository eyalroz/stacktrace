// Copyright Antony Polukhin, 2016-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

//[getting_started_trace_addresses
#include <stacktrace.hpp>
#include <iostream>     // std::cout

void dump_compact(const stacktrace_::stacktrace& st) {
    for (stacktrace_::frame frame: st) {
        std::cout << frame.address() << ',';
    }

    std::cout << std::endl;
}
//]

STACKTRACE_NOINLINE stacktrace_::stacktrace rec1(int i);
STACKTRACE_NOINLINE stacktrace_::stacktrace rec2(int i);

STACKTRACE_NOINLINE stacktrace_::stacktrace rec1(int i) {
    if (i < 5) {
        if (!i) return stacktrace_::stacktrace();
        return rec2(--i);
    }

    return rec2(i - 2);
}

STACKTRACE_NOINLINE stacktrace_::stacktrace rec2(int i) {
    if (i < 5) {
        if (!i) return stacktrace_::stacktrace();
        return rec2(--i);
    }

    return rec2(i - 2);
}

int main() {
    dump_compact(rec1(8));
}


