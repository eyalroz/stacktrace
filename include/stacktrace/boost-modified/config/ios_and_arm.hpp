/*
Copyright Rene Rivera 2008-2019
Copyright Franz Detro 2014
Copyright (c) Microsoft Corporation 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef STACKTRACE_BOOST_PREDEF_ARM_AND_IOS_HPP_
#define STACKTRACE_BOOST_PREDEF_ARM_AND_IOS_HPP_

// from ios.h

#define BOOST_OS_IOS 0

#if defined(__APPLE__) && defined(__MACH__) && \
    defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) 
#   undef BOOST_OS_IOS
#   define BOOST_OS_IOS (__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__*1000)
#endif

#if BOOST_OS_IOS
#   define BOOST_OS_IOS_AVAILABLE
#endif

// from arm.h

#define STACKTRACE_ARCH_ARM 0

#if \
    defined(__ARM_ARCH) || defined(__TARGET_ARCH_ARM) || \
    defined(__TARGET_ARCH_THUMB) || defined(_M_ARM) || \
    defined(__arm__) || defined(__arm64) || defined(__thumb__) || \
    defined(_M_ARM64) || defined(__aarch64__) || defined(__AARCH64EL__) || \
    defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || \
    defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || \
    defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || \
    defined(__ARM_ARCH_6KZ__) || defined(__ARM_ARCH_6T2__) || \
    defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__) || \
    defined(__ARM_ARCH_4T__) || defined(__ARM_ARCH_4__)
#   undef STACKTRACE_ARCH_ARM
#   if !defined(STACKTRACE_ARCH_ARM) && defined(__ARM_ARCH)
#       define STACKTRACE_ARCH_ARM __ARM_ARCH
#   endif
#   if !defined(STACKTRACE_ARCH_ARM) && defined(__TARGET_ARCH_ARM)
#       define STACKTRACE_ARCH_ARM __TARGET_ARCH_ARM
#   endif
#   if !defined(STACKTRACE_ARCH_ARM) && defined(__TARGET_ARCH_THUMB)
#       define STACKTRACE_ARCH_ARM __TARGET_ARCH_THUMB
#   endif
#   if !defined(STACKTRACE_ARCH_ARM) && defined(_M_ARM)
#       define STACKTRACE_ARCH_ARM _M_ARM
#   endif
#   if !defined(STACKTRACE_ARCH_ARM) && ( \
        defined(__arm64) || defined(_M_ARM64) || defined(__aarch64__) || \
        defined(__AARCH64EL__) )
#       define STACKTRACE_ARCH_ARM 8
#   endif
#   if !defined(STACKTRACE_ARCH_ARM) && ( \
    defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || \
    defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) )
#       define STACKTRACE_ARCH_ARM 7
#   endif
#   if !defined(STACKTRACE_ARCH_ARM) && ( \
    defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || \
    defined(__ARM_ARCH_6KZ__) || defined(__ARM_ARCH_6T2__) )
#       define STACKTRACE_ARCH_ARM 6
#   endif
#   if !defined(STACKTRACE_ARCH_ARM) && ( \
    defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__) )
#       define STACKTRACE_ARCH_ARM 5
#   endif
#   if !defined(STACKTRACE_ARCH_ARM) && ( \
    defined(__ARM_ARCH_4T__) || defined(__ARM_ARCH_4__) )
#       define STACKTRACE_ARCH_ARM 4
#   endif
#   if !defined(STACKTRACE_ARCH_ARM)
#       define STACKTRACE_ARCH_ARM 0_0_1
#   endif
#endif

#if STACKTRACE_ARCH_ARM > 0
#   define STACKTRACE_ARCH_ARM_AVAILABLE
#endif

#endif // STACKTRACE_BOOST_PREDEF_ARM_AND_IOS_HPP_
