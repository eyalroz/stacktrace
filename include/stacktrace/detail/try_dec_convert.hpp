// Copyright Antony Polukhin, 2016-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_TRY_DEC_CONVERT_HPP_
#define STACKTRACE_DETAIL_TRY_DEC_CONVERT_HPP_

#include <cstdlib>

namespace stacktrace_ { namespace detail {

inline bool try_dec_convert(const char* s, std::size_t& res) noexcept {
    char* end_ptr = 0;
    res = std::strtoul(s, &end_ptr, 10);
    return *end_ptr == '\0';
}


}} //  namespace stacktrace_::detail

#endif // STACKTRACE_DETAIL_TRY_DEC_CONVERT_HPP_
