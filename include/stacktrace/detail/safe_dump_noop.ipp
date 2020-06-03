// Copyright Antony Polukhin, 2016-2019.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_SAFE_DUMP_NOOPIPP_
#define STACKTRACE_DETAIL_SAFE_DUMP_NOOPIPP_

#include <stacktrace/safe_dump_to.hpp>

namespace stacktrace_ { namespace detail {


#if defined(STACKTRACE_WINDOWS)
std::size_t dump(void* /*fd*/, const native_frame_ptr_t* /*frames*/, std::size_t /*frames_count*/) noexcept {
    return 0;
}
#else
std::size_t dump(int /*fd*/, const native_frame_ptr_t* /*frames*/, std::size_t /*frames_count*/) noexcept {
    return 0;
}
#endif


std::size_t dump(const char* /*file*/, const native_frame_ptr_t* /*frames*/, std::size_t /*frames_count*/) noexcept {
    return 0;
}

}} //  namespace stacktrace_::detail

#endif // STACKTRACE_DETAIL_SAFE_DUMP_NOOPIPP_
