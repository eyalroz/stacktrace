// Copyright Antony Polukhin, 2016-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_TO_DEC_ARRAY_HPP_
#define STACKTRACE_DETAIL_TO_DEC_ARRAY_HPP_

#include <array>

namespace stacktrace_ { namespace detail {

inline std::array<char, 40> to_dec_array(std::size_t value) noexcept {
    std::array<char, 40> ret;
    if (!value) {
        ret[0] = '0';
        ret[1] = '\0';
        return ret;
    }

    std::size_t digits = 0;
    for (std::size_t value_copy = value; value_copy; value_copy /= 10) {
        ++ digits;
    }

    for (std::size_t i = 1; i <= digits; ++i) {
        ret[digits - i] = static_cast<char>('0' + (value % 10));
        value /= 10;
    }

    ret[digits] = '\0';

    return ret;
}


}} //  namespace stacktrace_::detail

#endif // STACKTRACE_DETAIL_TO_DEC_ARRAY_HPP_
