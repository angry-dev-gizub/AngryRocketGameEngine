
/*
 * Copyright 2026 Nelson Somé
 *
 * Licensed under the Apache License, Version 2.0.
 * See the LICENCE file in the project root for license information.
 */

/**
 * @file compiler.h
 *
 * @author Nelson Somé
 *
 * @brief Compiler identification and feature detection.
 *
 * @note This file is part of AngryRocketCore.
 */

#ifndef AR_COMPILER_H_
#define AR_COMPILER_H_

/* Compiler identification. */
#define AR_COMPILER_CLANG   0
#define AR_COMPILER_INTEL   0
#define AR_COMPILER_GCC     0
#define AR_COMPILER_MSVC    0
#define AR_COMPILER_UNKNOWN 0

#if defined(__INTEL_LLVM_COMPILER) || defined(__INTEL_COMPILER) || defined(__ICL)
#  undef AR_COMPILER_INTEL
#  define AR_COMPILER_INTEL 1
#  define AR_COMPILER_NAME "Intel"
#elif defined(__clang__)
#  undef AR_COMPILER_CLANG
#  define AR_COMPILER_CLANG 1
#  define AR_COMPILER_NAME "Clang"
#elif defined(__GNUC__)
#  undef AR_COMPILER_GCC
#  define AR_COMPILER_GCC 1
#  define AR_COMPILER_NAME "GCC"
#elif defined(_MSC_VER)
#  undef AR_COMPILER_MSVC
#  define AR_COMPILER_MSVC 1
#  define AR_COMPILER_NAME "MSVC"
#else
#  undef AR_COMPILER_UNKNOWN
#  define AR_COMPILER_UNKNOWN 1
#  define AR_COMPILER_NAME "Unknown"
#endif

/* Compiler feature detection. */
#if AR_COMPILER_GCC || AR_COMPILER_CLANG || AR_COMPILER_INTEL
#  define AR_HAS_FORCE_INLINE       1
#  define AR_HAS_NOINLINE           1
#  define AR_HAS_DEPRECATED         1
#  define AR_HAS_BRANCH_HINTS       1
#  define AR_HAS_UNREACHABLE        1
#  define AR_HAS_PACKED_STRUCTURES  1
#  define AR_HAS_FALLTHROUGH        1
#elif AR_COMPILER_MSVC
#  define AR_HAS_FORCE_INLINE       1
#  define AR_HAS_NOINLINE           1
#  define AR_HAS_DEPRECATED         1
#  define AR_HAS_BRANCH_HINTS       0
#  define AR_HAS_UNREACHABLE        1
#  define AR_HAS_PACKED_STRUCTURES  1
#  define AR_HAS_FALLTHROUGH        0
#else
#  define AR_HAS_FORCE_INLINE       0
#  define AR_HAS_NOINLINE           0
#  define AR_HAS_DEPRECATED         0
#  define AR_HAS_BRANCH_HINTS       0
#  define AR_HAS_UNREACHABLE        0
#  define AR_HAS_PACKED_STRUCTURES  0
#  define AR_HAS_FALLTHROUGH        0
#endif

#endif /* AR_COMPILER_H_ */
