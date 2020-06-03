//  A part of the Boost compiler configuration,
//  made up of some of select_compiler_config.hpp and some of the files
//  under config/compiler/

//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Martin Wille 2003.
//  (C) Copyright Guillaume Melquiond 2003.
//  De-boostification for stacktrace (C) Copyright Eyal Rozenberg 2020.
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//   http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for most recent version.

#ifndef STACKTRACE_COMPILER_RELATED_HPP_
#define  STACKTRACE_COMPILER_RELATED_HPP_


#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
//  Intel
#   define BOOST_INTEL
#if defined(__GNUC__) && (__GNUC__ >= 4)
#  define STACKTRACE_SYMBOL_EXPORT __attribute__((visibility("default")))
#  define STACKTRACE_SYMBOL_IMPORT
#  define STACKTRACE_SYMBOL_VISIBLE __attribute__((visibility("default")))
#endif


#elif defined __clang__ && !defined(__ibmxl__)
//  Clang C++ emulates GCC, so it has to appear early.
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__CYGWIN__)
#  define BOOST_HAS_DECLSPEC
#  define STACKTRACE_SYMBOL_EXPORT __attribute__((__dllexport__))
#  define STACKTRACE_SYMBOL_IMPORT __attribute__((__dllimport__))
#else
#  define STACKTRACE_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#  define STACKTRACE_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#  define STACKTRACE_SYMBOL_IMPORT
#endif

# elif defined(__GNUC__) && !defined(__ibmxl__)
//  GNU C++:
#if __GNUC__ >= 4
#  if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__CYGWIN__)
     // All Win32 development environments, including 64-bit Windows and MinGW, define
     // _WIN32 or one of its variant spellings. Note that Cygwin is a POSIX environment,
     // so does not define _WIN32 or its variants, but still supports dllexport/dllimport.
#    define BOOST_HAS_DECLSPEC
#    define STACKTRACE_SYMBOL_EXPORT __attribute__((__dllexport__))
#    define STACKTRACE_SYMBOL_IMPORT __attribute__((__dllimport__))
#  else
#    define STACKTRACE_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#    define STACKTRACE_SYMBOL_IMPORT
#  endif
#  define STACKTRACE_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#else
// config/platform/win32.hpp will define STACKTRACE_SYMBOL_EXPORT, etc., unless already defined
#  define STACKTRACE_SYMBOL_EXPORT
#endif


#elif defined  __SUNPRO_CC
//  Sun Workshop Compiler C++
#if __SUNPRO_CC > 0x500
#  define STACKTRACE_SYMBOL_EXPORT __global
#  define STACKTRACE_SYMBOL_IMPORT __global
#  define STACKTRACE_SYMBOL_VISIBLE __global
#endif

#elif defined(__ibmxl__)
//  IBM XL C/C++ for Linux (Little Endian)
#if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)
#  define STACKTRACE_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#  define STACKTRACE_SYMBOL_IMPORT
#  define STACKTRACE_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#endif

#elif defined _MSC_VER
//  Microsoft Visual C++
//
//  Must remain the last #elif since some other vendors (Metrowerks, for
//  example) also #define _MSC_VER
#   define BOOST_MSVC
#endif // compiler detection


//
// ensure that visibility macros are always defined, thus symplifying use
// (lifted from suffix.hpp)
//
#ifndef STACKTRACE_SYMBOL_EXPORT
# define STACKTRACE_SYMBOL_EXPORT
#endif
#ifndef STACKTRACE_SYMBOL_IMPORT
# define STACKTRACE_SYMBOL_IMPORT
#endif
#ifndef STACKTRACE_SYMBOL_VISIBLE
# define STACKTRACE_SYMBOL_VISIBLE
#endif


#endif // STACKTRACE_COMPILER_RELATED_HPP_
