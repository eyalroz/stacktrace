// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_DETAIL_VOID_PTR_CAST_HPP_
#define STACKTRACE_DETAIL_VOID_PTR_CAST_HPP_

#if defined(__GNUC__) && defined(__GNUC_MINOR__) && (__GNUC__ * 100 + __GNUC_MINOR__ > 301)
#   pragma GCC system_header
#endif

namespace stacktrace_ { namespace detail {

// GCC warns when reinterpret_cast between function pointer and object pointer occur.
// This functionsuppress the warnings and ensures that such casts are safe.
template <class To, class From>
To void_ptr_cast(From* v) noexcept {
    static_assert(
        std::is_pointer<To>::value,
        "`void_ptr_cast` function must be used only for casting to or from void pointers."
    );

    static_assert(
        sizeof(From*) == sizeof(To),
        "Pointer to function and pointer to object differ in size on your platform."
    );

    return reinterpret_cast<To>(v);
}


}} // stacktrace_::detail

#endif // STACKTRACE_DETAIL_VOID_PTR_CAST_HPP_

