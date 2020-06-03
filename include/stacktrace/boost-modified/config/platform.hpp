//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

// This file is a snippet taken out of some of the Boost configuration headers - win32.hpp and select_platform_config.hpp

#ifndef STACKTRACE_PLATFORM_HPP_
#define STACKTRACE_PLATFORM_HPP_
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define STACKTRACE_WINDOWS 1
#endif

#endif // STACKTRACE_PLATFORM_HPP_
