// Copyright Antony Polukhin, 2016-2019.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_FRAME_NOOPIPP_
#define STACKTRACE_DETAIL_FRAME_NOOPIPP_

#include <stacktrace/frame.hpp>

namespace stacktrace_ { namespace detail {

std::string to_string(const frame* /*frames*/, std::size_t /*count*/) {
    return std::string();
}

} // namespace detail

std::string frame::name() const {
    return std::string();
}

std::string frame::source_file() const {
    return std::string();
}

std::size_t frame::source_line() const {
    return 0;
}

std::string to_string(const frame& /*f*/) {
    return std::string();
}


} //  namespace stacktrace_

#endif // STACKTRACE_DETAIL_FRAME_NOOPIPP_
