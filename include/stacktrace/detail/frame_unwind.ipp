// Copyright Antony Polukhin, 2016-2019.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_FRAME_UNWIND_IPP
#define STACKTRACE_DETAIL_FRAME_UNWIND_IPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <stacktrace/frame.hpp>

#include <stacktrace/detail/to_hex_array.hpp>
#include <stacktrace/detail/location_from_symbol.hpp>
#include <stacktrace/detail/to_dec_array.hpp>
#include <boost/core/demangle.hpp>

#include <cstdio>

#ifdef STACKTRACE_USE_BACKTRACE
#   include <stacktrace/detail/libbacktrace_impls.hpp>
#elif defined(STACKTRACE_USE_ADDR2LINE)
#   include <stacktrace/detail/addr2line_impls.hpp>
#else
#   include <stacktrace/detail/unwind_base_impls.hpp>
#endif

namespace stacktrace { namespace detail {

template <class Base>
class to_string_impl_base: private Base {
public:
    std::string operator()(stacktrace::detail::native_frame_ptr_t addr) {
        Base::res.clear();
        Base::prepare_function_name(addr);
        if (!Base::res.empty()) {
            Base::res = boost::core::demangle(Base::res.c_str());
        } else {
            Base::res = to_hex_array(addr).data();
        }

        if (Base::prepare_source_location(addr)) {
            return Base::res;
        }

        stacktrace::detail::location_from_symbol loc(addr);
        if (!loc.empty()) {
            Base::res += " in ";
            Base::res += loc.name();
        }

        return Base::res;
    }
};

std::string to_string(const frame* frames, std::size_t size) {
    std::string res;
    if (size == 0) {
        return res;
    }
    res.reserve(64 * size);

    to_string_impl impl;

    for (std::size_t i = 0; i < size; ++i) {
        if (i < 10) {
            res += ' ';
        }
        res += stacktrace::detail::to_dec_array(i).data();
        res += '#';
        res += ' ';
        res += impl(frames[i].address());
        res += '\n';
    }

    return res;
}


} // namespace detail


std::string frame::name() const {
    if (!addr_) {
        return std::string();
    }

#if !defined(BOOST_WINDOWS) && !defined(__CYGWIN__)
    ::Dl_info dli;
    const bool dl_ok = !!::dladdr(const_cast<void*>(addr_), &dli); // `dladdr` on Solaris accepts nonconst addresses
    if (dl_ok && dli.dli_sname) {
        return boost::core::demangle(dli.dli_sname);
    }
#endif
    return stacktrace::detail::name_impl(addr_);
}

std::string to_string(const frame& f) {
    if (!f) {
        return std::string();
    }

    stacktrace::detail::to_string_impl impl;
    return impl(f.address());
}


}} // namespace boost::stacktrace

#endif // STACKTRACE_DETAIL_FRAME_UNWIND_IPP
