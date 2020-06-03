// Copyright Antony Polukhin, 2016-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef STACKTRACE_FRAME_HPP_
#define STACKTRACE_FRAME_HPP_

#include <iosfwd>
#include <string>

// There was an inclusion of an explicit_operator_bool.hpp file from Boost - but it seems not to be used anywhere.

#include <stacktrace/safe_dump_to.hpp> // stacktrace_::detail::native_frame_ptr_t

#include <stacktrace/detail/frame_decl.hpp>
#include <stacktrace/detail/push_options.h>

namespace stacktrace_ {

/// Comparison operators that provide platform dependant ordering and have O(1) complexity; are Async-Handler-Safe.
constexpr inline bool operator< (const frame& lhs, const frame& rhs) noexcept { return lhs.address() < rhs.address(); }
constexpr inline bool operator> (const frame& lhs, const frame& rhs) noexcept { return rhs < lhs; }
constexpr inline bool operator<=(const frame& lhs, const frame& rhs) noexcept { return !(lhs > rhs); }
constexpr inline bool operator>=(const frame& lhs, const frame& rhs) noexcept { return !(lhs < rhs); }
constexpr inline bool operator==(const frame& lhs, const frame& rhs) noexcept { return lhs.address() == rhs.address(); }
constexpr inline bool operator!=(const frame& lhs, const frame& rhs) noexcept { return !(lhs == rhs); }

/// Fast hashing support, O(1) complexity; Async-Handler-Safe.
inline std::size_t hash_value(const frame& f) noexcept {
    return reinterpret_cast<std::size_t>(f.address());
}

/// Outputs stacktrace_::frame in a human readable format to string; unsafe to use in async handlers.
std::string to_string(const frame& f);

/// Outputs stacktrace_::frame in a human readable format to output stream; unsafe to use in async handlers.
template <class CharT, class TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& os, const frame& f) {
    return os << stacktrace_::to_string(f);
}

} //  namespace stacktrace_

/// @cond

#include <stacktrace/detail/pop_options.h>

#ifndef STACKTRACE_LINK
#   if defined(STACKTRACE_USE_NOOP)
#       include <stacktrace/detail/frame_noop.ipp>
#   elif defined(BOOST_MSVC) || defined(STACKTRACE_USE_WINDBG) || defined(STACKTRACE_USE_WINDBG_CACHED)
#       include <stacktrace/detail/frame_msvc.ipp>
#   else
#       include <stacktrace/detail/frame_unwind.ipp>
#   endif
#endif
/// @endcond


#endif // STACKTRACE_FRAME_HPP_
