/*
 * Copyright 2026 Nelson Somé
 *
 * Licensed under the Apache License, Version 2.0.
 * See the LICENCE file in the project root for license information.
 */

/**
 * @file assertion.h
 *
 * @author Nelson Somé
 *
 * @brief Compile-time and runtime assertion macros.
 *
 * @note This file is part of AngryRocketCore.
 */

#ifndef AR_ASSERTION_H_
#define AR_ASSERTION_H_

#include "attributes.h"

#if defined(__cplusplus) || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 202311L))
#  define AR_STATIC_ASSERT(expr, msg) static_assert(expr, msg)
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#  define AR_STATIC_ASSERT(expr, msg) _Static_assert(expr, msg)
#else
#  define AR_STATIC_ASSERT_JOIN(a, b) a##b
#  define AR_STATIC_ASSERT_IMPL(expr, line) \
       typedef char AR_STATIC_ASSERT_JOIN(ar_static_assert_, line)[(expr) ? 1 : -1]
#  define AR_STATIC_ASSERT(expr, msg) AR_STATIC_ASSERT_IMPL(expr, __LINE__)
#endif

#if AR_COMPILER_MSVC
#  define AR_DEBUG_BREAK() __debugbreak()
#elif AR_COMPILER_GCC || AR_COMPILER_CLANG || AR_COMPILER_INTEL
#  define AR_DEBUG_BREAK() __builtin_trap()
#else
#  include <stdlib.h>
#  define AR_DEBUG_BREAK() abort()
#endif

#if !defined(AR_ENABLE_ASSERTS)
#  if defined(AR_DEBUG)
#    define AR_ENABLE_ASSERTS 1
#  else
#    define AR_ENABLE_ASSERTS 0
#  endif
#endif

AR_EXTERN_C_BEGIN

/**
 * @brief Reports a runtime assertion failure and terminates execution.
 *
 * @param[in] expr Stringified expression that evaluated to false.
 * @param[in] message Optional human-readable diagnostic message (may be NULL).
 * @param[in] file Source file path where the assertion failed.
 * @param[in] line Line number where the assertion failed.
 */
AR_API AR_NORETURN void ar_assert_fail(
    const char* expr,
    const char* message,
    const char* file,
    int line
);

AR_EXTERN_C_END

#if AR_ENABLE_ASSERTS
#  define AR_ASSERT_MSG(expr, msg)                                       \
       do {                                                              \
           if (AR_UNLIKELY(!(expr))) {                                   \
               ar_assert_fail(#expr, (msg), __FILE__, __LINE__);         \
           }                                                             \
       } while (0)

#  define AR_ASSERT(expr) AR_ASSERT_MSG(expr, NULL)
#else
#  define AR_ASSERT_MSG(expr, msg) ((void)sizeof(expr), (void)sizeof(msg))
#  define AR_ASSERT(expr)          ((void)sizeof(expr))
#endif

#endif /* AR_ASSERTION_H_ */
