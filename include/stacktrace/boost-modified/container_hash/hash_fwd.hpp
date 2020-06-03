
// Copyright 2005-2009 Daniel James.
// Copyright 2020 Eyal Rozenberg.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18. 

#if !defined(STACKTRACE_BOOST_FUNCTIONAL_HASH_FWD_HPP)
#define STACKTRACE_BOOST_FUNCTIONAL_HASH_FWDHPP_

#include <cstddef>

namespace stacktrace_ {

    template <class T> struct hash;

    template <class T> void hash_combine(std::size_t& seed, T const& v);

    template <class It> std::size_t hash_range(It, It);
    template <class It> void hash_range(std::size_t&, It, It);

#ifdef __BORLANDC__
// This condition was originally
// 
//    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
//
// i.e. it might be necessary to check the BORLANDC version
    template <class T> inline std::size_t hash_range(T*, T*);
    template <class T> inline void hash_range(std::size_t&, T*, T*);
#endif

} //  namespace stacktrace_

#endif // STACKTRACE_BOOST_FUNCTIONAL_HASH_FWDHPP_
