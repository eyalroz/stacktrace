// Copyright Antony Polukhin, 2016-2019.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// No include guards! Intentionally.

// Link or header only
#if !defined(STACKTRACE_LINK) && defined(STACKTRACE_DYN_LINK)
#   define STACKTRACE_LINK
#endif

#ifdef STACKTRACE_LINK
#   if defined(STACKTRACE_DYN_LINK)
#       ifdef STACKTRACE_INTERNAL_BUILD_LIBS
#           define STACKTRACE_SYMBOL_EXPORT
#       else
#           define STACKTRACE_SYMBOL_IMPORT
#       endif
#   else
#       define STACKTRACE_FUNCTION
#   endif
#elif !defined(STACKTRACE_DOXYGEN_INVOKED)
#   define STACKTRACE_FUNCTION inline
#endif

