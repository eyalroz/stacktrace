// Copyright Antony Polukhin, 2016-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_TRY_DEC_CONVERT_HPP_
#define STACKTRACE_DETAIL_TRY_DEC_CONVERT_HPP_

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <cstdlib>

namespace stacktrace { namespace detail {

// We do not use boost::lexical_cast in this function to reduce module dependencies
inline bool try_dec_convert(const char* s, std::size_t& res) BOOST_NOEXCEPT {
    char* end_ptr = 0;
    res = std::strtoul(s, &end_ptr, 10);
    return *end_ptr == '\0';
}


}}} // namespace stacktrace::detail

#endif // STACKTRACE_DETAIL_TRY_DEC_CONVERT_HPP_
