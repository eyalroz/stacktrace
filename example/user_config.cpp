// Copyright Antony Polukhin, 2016-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "user_config.hpp"

#include <stacktrace.hpp>

#include <iostream>     // std::cerr
#include <array>
#include <exception>    // std::set_terminate, std::abort
STACKTRACE_NOINLINE void foo(int i);
STACKTRACE_NOINLINE void bar(int i);
 
STACKTRACE_NOINLINE void bar(int i) {
    std::array<int, 5> a = {{-1, -231, -123, -23, -32}};
    if (i >= 0) {
        foo(a[i]);
    } else {
        std::cerr << "Terminate called:\n" << stacktrace_::stacktrace() << '\n';
        std::exit(0);
    }
}

STACKTRACE_NOINLINE void foo(int i) {
    bar(--i);
}

int main() {
    foo(5);
    
    return 2;
}
