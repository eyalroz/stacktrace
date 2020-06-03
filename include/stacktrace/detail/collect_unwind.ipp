// Copyright Antony Polukhin, 2016-2019.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_COLLECT_UNWIND_IPP
#define STACKTRACE_DETAIL_COLLECT_UNWIND_IPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <stacktrace/safe_dump_to.hpp>

// On iOS 32-bit ARM architecture _Unwind_Backtrace function doesn't exist, symbol is undefined.
// Forcing libc backtrace() function usage.
#include <boost/predef.h>
#if defined(BOOST_OS_IOS_AVAILABLE) && defined(BOOST_ARCH_ARM_AVAILABLE) && BOOST_VERSION_NUMBER_MAJOR(BOOST_ARCH_ARM) < 8
#define STACKTRACE_USE_LIBC_BACKTRACE_FUNCTION
#endif

#if defined(STACKTRACE_USE_LIBC_BACKTRACE_FUNCTION)
#include <execinfo.h>
#include <algorithm>
#else
#include <unwind.h>
#endif
#include <cstdio>

#if !defined(_GNU_SOURCE) && !defined(STACKTRACE_GNU_SOURCE_NOT_REQUIRED) && !defined(BOOST_WINDOWS)
#error "Boost.Stacktrace requires `_Unwind_Backtrace` function. Define `_GNU_SOURCE` macro or `STACKTRACE_GNU_SOURCE_NOT_REQUIRED` if _Unwind_Backtrace is available without `_GNU_SOURCE`."
#endif

namespace stacktrace { namespace detail {

#if !defined(STACKTRACE_USE_LIBC_BACKTRACE_FUNCTION)
struct unwind_state {
    std::size_t frames_to_skip;
    native_frame_ptr_t* current;
    native_frame_ptr_t* end;
};

inline _Unwind_Reason_Code unwind_callback(::_Unwind_Context* context, void* arg) {
    // Note: do not write `::_Unwind_GetIP` because it is a macro on some platforms.
    // Use `_Unwind_GetIP` instead!
    unwind_state* const state = static_cast<unwind_state*>(arg);
    if (state->frames_to_skip) {
        --state->frames_to_skip;
        return _Unwind_GetIP(context) ? ::_URC_NO_REASON : ::_URC_END_OF_STACK;
    }

    *state->current =  reinterpret_cast<native_frame_ptr_t>(
        _Unwind_GetIP(context)
    );

    ++state->current;
    if (!*(state->current - 1) || state->current == state->end) {
        return ::_URC_END_OF_STACK;
    }
    return ::_URC_NO_REASON;
}
#endif //!defined(STACKTRACE_USE_LIBC_BACKTRACE_FUNCTION)

std::size_t this_thread_frames::collect(native_frame_ptr_t* out_frames, std::size_t max_frames_count, std::size_t skip) BOOST_NOEXCEPT {
    std::size_t frames_count = 0;
    if (!max_frames_count) {
        return frames_count;
    }
    skip += 1;

#if defined(STACKTRACE_USE_LIBC_BACKTRACE_FUNCTION)
    // According to https://opensource.apple.com/source/Libc/Libc-1272.200.26/gen/backtrace.c.auto.html
    // it looks like the `::backtrace` is async signal safe.
    frames_count = static_cast<size_t>(::backtrace(const_cast<void **>(out_frames), static_cast<int>(max_frames_count)));

    // NOTE: There is no way to pass "skip" count to backtrace function so we need to perform left shift operation.
    // If number of elements in result backtrace is >= max_frames_count then "skip" elements are wasted.
    if (frames_count && skip) {
        if (skip >= frames_count) {
            frames_count = 0;
        } else {
            std::copy(out_frames + skip, out_frames + frames_count, out_frames);
            frames_count -= skip;
        }
    }
#else
    stacktrace::detail::unwind_state state = { skip, out_frames, out_frames + max_frames_count };
    ::_Unwind_Backtrace(&stacktrace::detail::unwind_callback, &state);
    frames_count = state.current - out_frames;
#endif //defined(STACKTRACE_USE_LIBC_BACKTRACE_FUNCTION)

    if (frames_count && out_frames[frames_count - 1] == 0) {
        -- frames_count;
    }

    return frames_count;
}


}}} // namespace stacktrace::detail

#undef STACKTRACE_USE_LIBC_BACKTRACE_FUNCTION

#endif // STACKTRACE_DETAIL_COLLECT_UNWIND_IPP
