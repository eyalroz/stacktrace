//  Modified Boost config.hpp configuration header file  ------------------------------//
//  boostinspect:ndprecated_macros -- tell the inspect tool to ignore this file

//  Copyright (c) 2001-2003 John Maddock
//  Copyright (c) 2001 Darin Adler
//  Copyright (c) 2001 Peter Dimov
//  Copyright (c) 2002 Bill Kempf
//  Copyright (c) 2002 Jens Maurer
//  Copyright (c) 2002-2003 David Abrahams
//  Copyright (c) 2003 Gennaro Prota
//  Copyright (c) 2003 Eric Friedman
//  Copyright (c) 2010 Eric Jourdanneau, Joel Falcou
//  De-boostification for stacktrace Copyright (c) 2020 Eyal Rozenberg
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for most recent version.

//  Boost config.hpp policy and rationale documentation has been moved to
//  http://www.boost.org/libs/config/
//
//  This file is intended to be stable, and relatively unchanging.
//  It should contain boilerplate code only - no compiler specific
//  code unless it is unavoidable - no changes unless unavoidable.

#ifndef STACKTRACE_BOOST_CONFIG_SUFFIX_HPP_
#define STACKTRACE_BOOST_CONFIG_SUFFIX_HPP_

#if defined(__GNUC__) && (__GNUC__ >= 4)
//
// Some GCC-4.x versions issue warnings even when __extension__ is used,
// so use this as a workaround:
//
#pragma GCC system_header
#endif

// STACKTRACE_FORCEINLINE ---------------------------------------------//
// Macro to use in place of 'inline' to force a function to be inline
#if !defined(STACKTRACE_FORCEINLINE)
#  if defined(_MSC_VER)
#    define STACKTRACE_FORCEINLINE __forceinline
#  elif defined(__GNUC__) && __GNUC__ > 3
     // Clang also defines __GNUC__ (as 4)
#    define STACKTRACE_FORCEINLINE inline __attribute__ ((__always_inline__))
#  else
#    define STACKTRACE_FORCEINLINE inline
#  endif
#endif

// STACKTRACE_NOINLINE ---------------------------------------------//
// Macro to use in place of 'inline' to prevent a function to be inlined
#if !defined(STACKTRACE_NOINLINE)
#  if defined(_MSC_VER)
#    define STACKTRACE_NOINLINE __declspec(noinline)
#  elif defined(__GNUC__) && __GNUC__ > 3
     // Clang also defines __GNUC__ (as 4)
#    if defined(__CUDACC__)
       // nvcc doesn't always parse __noinline__,
       // see: https://svn.boost.org/trac/boost/ticket/9392
#      define STACKTRACE_NOINLINE __attribute__ ((noinline))
#    else
#      define STACKTRACE_NOINLINE __attribute__ ((__noinline__))
#    endif
#  else
#    define STACKTRACE_NOINLINE
#  endif
#endif

#endif // STACKTRACE_BOOST_CONFIG_SUFFIX_HPP_
