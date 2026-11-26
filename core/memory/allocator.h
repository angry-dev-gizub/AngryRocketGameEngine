/*
 * Copyright 2026 Nelson Somé
 *
 * Licensed under the Apache License, Version 2.0.
 * See the LICENCE file in the project root for license information.
 */

/**
 * @file allocator.h
 * 
 * @author Nelson Somé
 * 
 * @brief Generic allocator interface.
 *
 * Wraps heap, pool, arena, and user-defined allocation strategies.
 * Every callback and memory-operation wrapper returns ARResult. Operations
 * producing a pointer write it through a caller-supplied output parameter.
 *
 * @note This file is part of AngryRocketCore.
 */

#ifndef AR_ALLOCATOR_H_
#define AR_ALLOCATOR_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "attributes.h"
#include "result.h"

/** Allocator error domain. */
#define AR_ERROR_DOMAIN_ALLOCATOR ((uint8_t)1U)

AR_EXTERN_C_BEGIN

/* forward declaration */
typedef struct ARAllocatorDesc_t ARAllocatorDesc;
typedef struct ARAllocatorInterface_t ARAllocatorInterface;
typedef struct ARAllocator_t ARAllocator;
typedef struct ARAdvancedAllocatorInterface_t ARAdvancedAllocatorInterface;
typedef struct ARAdvancedAllocatorDesc_t ARAdvancedAllocatorDesc;
typedef struct ARAdvancedAllocator_t ARAdvancedAllocator;

typedef ARResult (*ARAllocFn)(void* context, void** out_ptr, size_t size);
typedef ARResult (*ARZeroAllocFn)(void* context, void** out_ptr, size_t size);
typedef ARResult (*ARReallocFn)(void* context, void** out_ptr, void* ptr, size_t new_size);
typedef ARResult (*ARAlignAllocFn)(void* context, void** out_ptr, size_t alignment, size_t size);
typedef ARResult (*ARAlignZeroAllocFn)(void* context, void** out_ptr, size_t alignment, size_t size);
typedef ARResult (*ARAlignReallocFn)(void* context, void** out_ptr, void* ptr, size_t alignment, size_t new_size);
typedef ARResult (*ARAdvancedReallocFn)(void* context, void** out_ptr, void* old_ptr, size_t old_size, size_t new_size);
typedef void (*ARFreeFn)(void* context, void* ptr);
typedef void (*ARAlignFreeFn)(void* context, void* ptr);
typedef void (*ARAdvancedFreeFn)(void* context, void** ptr);
typedef void (*ARClearFn)(void* context);

struct ARAllocatorInterface_t
{
    AR_PUBLIC ARAllocFn allocate;
    AR_PUBLIC ARZeroAllocFn zero_allocate;
    AR_PUBLIC ARReallocFn reallocate;
    AR_PUBLIC ARFreeFn deallocate;
    AR_PUBLIC ARClearFn clear;
};

struct ARAdvancedAllocatorInterface_t
{
    AR_PUBLIC ARAllocFn allocate;
    AR_PUBLIC ARZeroAllocFn zero_allocate;
    AR_PUBLIC ARReallocFn reallocate;
    AR_PUBLIC ARFreeFn deallocate;
    AR_PUBLIC ARClearFn clear;
    
    AR_PUBLIC ARAlignAllocFn align_allocate;
    AR_PUBLIC ARAlignZeroAllocFn align_zero_allocate;
    AR_PUBLIC ARAlignReallocFn align_reallocate;
    AR_PUBLIC ARAdvancedReallocFn advanced_reallocate;
    AR_PUBLIC ARAlignFreeFn align_deallocate;
    AR_PUBLIC ARAdvancedFreeFn advanced_deallocate;
};

struct ARAllocatorDesc_t
{
    AR_PUBLIC void* context;
    AR_PUBLIC ARAllocatorInterface interface;
};

struct ARAdvancedAllocatorDesc_t
{
    AR_PUBLIC void* context;
    AR_PUBLIC ARAdvancedAllocatorInterface interface;
};

struct ARAllocator_t
{
    AR_PRIVATE void* context;
    AR_PRIVATE ARAllocatorInterface interface;
};

struct ARAdvancedAllocator_t
{
    AR_PRIVATE void* context;
    AR_PRIVATE ARAdvancedAllocatorInterface interface;
};

AR_EXTERN_C_END

#endif /* AR_ALLOCATOR_H_ */
