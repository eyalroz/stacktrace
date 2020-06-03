// Copyright Antony Polukhin, 2016-2019.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_COLLECT_NOOPIPP_
#define STACKTRACE_DETAIL_COLLECT_NOOPIPP_

#include <stacktrace/safe_dump_to.hpp>

namespace stacktrace_ { namespace detail {

std::size_t this_thread_frames::collect(native_frame_ptr_t* /*out_frames*/, std::size_t /*max_frames_count*/, std::size_t /*skip*/) noexcept {
    return 0;
}

}} //  namespace stacktrace_::detail

#endif // STACKTRACE_DETAIL_COLLECT_NOOPIPP_
