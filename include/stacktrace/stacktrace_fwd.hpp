// Copyright Antony Polukhin, 2016-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_STACKTRACE_FWD_HPP_
#define STACKTRACE_STACKTRACE_FWD_HPP_

#include <cstddef>
#include <memory>

/// @file stacktrace_fwd.hpp This header contains only forward declarations of
/// stacktrace::frame, stacktrace::basic_stacktrace, stacktrace::stacktrace
/// and does not include any other Boost headers.

/// @cond
namespace stacktrace {

class frame;
template <class Allocator = std::allocator<frame> > class basic_stacktrace;
typedef basic_stacktrace<> stacktrace;

}} // namespace boost::stacktrace
/// @endcond


#endif // STACKTRACE_STACKTRACE_FWD_HPP_
