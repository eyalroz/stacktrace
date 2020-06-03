// Copyright Antony Polukhin, 2016-2019.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_COLLECT_MSVC_IPP_
#define STACKTRACE_DETAIL_COLLECT_MSVC_IPP_

#include <stacktrace/safe_dump_to.hpp>
#include <boost/winapi/stack_backtrace.hpp>

namespace stacktrace_ { 
namespace detail {

std::size_t this_thread_frames::collect(native_frame_ptr_t* out_frames, std::size_t max_frames_count, std::size_t skip) BOOST_NOEXCEPT 
{
    return boost::winapi::RtlCaptureStackBackTrace(
        static_cast<boost::winapi::ULONG_>(skip),
        static_cast<boost::winapi::ULONG_>(max_frames_count),
        const_cast<boost::winapi::PVOID_*>(out_frames),
        0
    );
}

} // namespace detail
} // namespace stacktrace_

#endif // STACKTRACE_DETAIL_COLLECT_MSVC_IPP_
