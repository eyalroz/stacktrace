// Copyright Antony Polukhin, 2016-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define STACKTRACE_INTERNAL_BUILD_LIBS
#define STACKTRACE_USE_BACKTRACE
#define STACKTRACE_LINK

#ifndef _GNU_SOURCE
#   define _GNU_SOURCE
#endif

#include <stacktrace/detail/frame_unwind.ipp>
#include <stacktrace/safe_dump_to.hpp>
