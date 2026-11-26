/*
 * Copyright 2026 Nelson Somé
 *
 * Licensed under the Apache License, Version 2.0.
 * See the LICENCE file in the project root for license information.
 */

/**
 * @file attributes.h
 *
 * @author Nelson Somé
 *
 * @brief Portable compiler attribute, alignment, and packing wrappers.
 *
 * @note This file is part of AngryRocketCore.
 */

#ifndef AR_ATTRIBUTES_H_
#define AR_ATTRIBUTES_H_

#include <stddef.h>
#include "compiler.h"

/* Function attributes. */
#define AR_INLINE static inline

#if AR_COMPILER_GCC || AR_COMPILER_CLANG || AR_COMPILER_INTEL
#  define AR_FORCE_INLINE static inline __attribute__((always_inline))
#  define AR_NOINLINE     __attribute__((noinline))
#  define AR_DEPRECATED(msg) __attribute__((deprecated(msg)))
#elif AR_COMPILER_MSVC
#  define AR_FORCE_INLINE static __forceinline
#  define AR_NOINLINE     __declspec(noinline)
#  define AR_DEPRECATED(msg) __declspec(deprecated(msg))
#else
#  define AR_FORCE_INLINE static inline
#  define AR_NOINLINE
#  define AR_DEPRECATED(msg)
#endif

#ifdef __cplusplus
#  define AR_NORETURN [[noreturn]]
#else
#  define AR_NORETURN _Noreturn
#endif

/* Unused expression suppression. */
#define AR_UNUSED(value) ((void)(value))

/* Branch prediction hints. */
#if AR_COMPILER_GCC || AR_COMPILER_CLANG || AR_COMPILER_INTEL
#  define AR_LIKELY(x)   __builtin_expect(!!(x), 1)
#  define AR_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#  define AR_LIKELY(x)   (!!(x))
#  define AR_UNLIKELY(x) (!!(x))
#endif

/* Unreachable-code hints. */
#if AR_COMPILER_GCC || AR_COMPILER_CLANG || AR_COMPILER_INTEL
#  define AR_UNREACHABLE() __builtin_unreachable()
#elif AR_COMPILER_MSVC
#  define AR_UNREACHABLE() __assume(0)
#else
#  define AR_UNREACHABLE() ((void)0)
#endif

/* Alignment. */
#ifdef __cplusplus
#  define AR_ALIGNAS(bytes) alignas(bytes)
#  define AR_ALIGNOF(type)  alignof(type)
#else
#  define AR_ALIGNAS(bytes) _Alignas(bytes)
#  define AR_ALIGNOF(type)  _Alignof(type)
#endif


/* Structure packing. */
#define AR_STRINGIFY_IMPL(value) #value
#define AR_STRINGIFY(value)      AR_STRINGIFY_IMPL(value)

#if AR_COMPILER_GCC || AR_COMPILER_CLANG || AR_COMPILER_INTEL
#  define AR_PACKED __attribute__((packed))
#  define AR_PACK_PUSH(bytes) _Pragma("pack(push, " AR_STRINGIFY(bytes) ")")
#  define AR_PACK_POP()       _Pragma("pack(pop)")
#elif AR_COMPILER_MSVC
#  define AR_PACKED
#  define AR_PACK_PUSH(bytes) __pragma(pack(push, bytes))
#  define AR_PACK_POP()       __pragma(pack(pop))
#else
#  define AR_PACKED
#  define AR_PACK_PUSH(bytes)
#  define AR_PACK_POP()
#endif

/* Fallthrough annotation. */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 202311L)
#  define AR_FALLTHROUGH [[fallthrough]]
#elif AR_COMPILER_GCC || AR_COMPILER_CLANG
#  define AR_FALLTHROUGH __attribute__((fallthrough))
#else
#  define AR_FALLTHROUGH
#endif

/* Shared-library visibility. */
#if defined(_WIN32) || defined(__CYGWIN__)
#  if AR_COMPILER_GCC || AR_COMPILER_CLANG
#    define AR_API_EXPORT __attribute__((dllexport))
#    define AR_API_IMPORT __attribute__((dllimport))
#  else
#    define AR_API_EXPORT __declspec(dllexport)
#    define AR_API_IMPORT __declspec(dllimport)
#  endif
#elif AR_COMPILER_GCC || AR_COMPILER_CLANG || AR_COMPILER_INTEL
#  define AR_API_EXPORT __attribute__((visibility("default")))
#  define AR_API_IMPORT
#else
#  define AR_API_EXPORT
#  define AR_API_IMPORT
#endif

/* API linkage selection. */
#if defined(AR_BUILD_SHARED) && defined(AR_USE_SHARED)
#  error "AngryRocketCore: AR_BUILD_SHARED and AR_USE_SHARED cannot both be defined."
#endif

#if defined(AR_BUILD_SHARED)
#  define AR_API AR_API_EXPORT
#elif defined(AR_USE_SHARED)
#  define AR_API AR_API_IMPORT
#else
#  define AR_API
#endif

/* C and C++ linkage compatibility. */
#ifdef __cplusplus
#  define AR_EXTERN_C_BEGIN extern "C" {
#  define AR_EXTERN_C_END   }
#else
#  define AR_EXTERN_C_BEGIN
#  define AR_EXTERN_C_END
#endif

/* Utility macro. */
#define AR_OFFSETOF(structure, member) offsetof(structure, member)

/* Documentation annotations. */
#define AR_PUBLIC
#define AR_PRIVATE

#endif /* AR_ATTRIBUTES_H_ */
