// Copyright Antony Polukhin, 2016-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_UNWIND_BASE_IMPLS_HPP_
#define STACKTRACE_DETAIL_UNWIND_BASE_IMPLS_HPP_

#include <stacktrace/frame.hpp>

namespace stacktrace_ { namespace detail {

struct to_string_using_nothing {
    std::string res;

    void prepare_function_name(const void* addr) {
        res = stacktrace_::frame(addr).name();
    }

    bool prepare_source_location(const void* /*addr*/) const noexcept {
        return false;
    }
};

template <class Base> class to_string_impl_base;
typedef to_string_impl_base<to_string_using_nothing> to_string_impl;

inline std::string name_impl(const void* /*addr*/) {
    return std::string();
}

} // namespace detail

std::string frame::source_file() const {
    return std::string();
}

std::size_t frame::source_line() const {
    return 0;
}

} //  namespace stacktrace_

#endif // STACKTRACE_DETAIL_UNWIND_BASE_IMPLS_HPP_
