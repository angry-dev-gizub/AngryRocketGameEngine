/*
 * Copyright 2026 Nelson Somé
 *
 * Licensed under the Apache License, Version 2.0.
 * See the LICENCE file in the project root for license information.
 */

/**
 * @file result.h
 *
 * @author Nelson Somé
 *
 * @brief Generic operation result representation.
 *
 * Provides a common result model for Arc Core operations using a packed
 * uint64_t error value with numeric layout 0xLLSSDDXXCCCCCCCC.
 * 
 * Callers inspect 'ok'; no separate public validity check is required.
 *
 * @note This file is part of Arc Core.
 */

#ifndef AR_RESULT_H_
#define AR_RESULT_H_

#include <stdint.h>
#include <stdbool.h>
#include "attributes.h"

/**
 * @brief Convenience macro for propagating a Result failure.
 *
 * Evaluates 'expr' and returns its Result if it is a failure. Otherwise
 * execution continues normally.
 *
 * @param[in] expr Expression that evaluates to an ARResult.
 *
 * @post On failure, the Result returned by 'expr' is returned from the
 *       enclosing function.
 */
#define AR_TRY(expr)                                             \
    do {                                                         \
        ARResult ar_try_result_from_expression_ = (expr);        \
        if (AR_UNLIKELY(!ar_try_result_from_expression_.ok)) {   \
            return ar_try_result_from_expression_;               \
        }                                                        \
    } while (0)


AR_EXTERN_C_BEGIN

/* Result type. */
typedef struct ARResult_t ARResult;

/**
 * @brief Generic operation Result.
 *
 * An ARResult represents either success or failure.
 *
 * @note Failure requires a recognized non-NONE severity. Domain and code
 *       identifiers need not be recognized by this implementation. Domain zero
 *       is the common domain and is valid on failure. Each operation documents
 *       which error values it can return.
 *
 * @attention Manually constructed or modified Results must satisfy these same
 *            invariants. Constructors cannot enforce invariants after a caller
 *            changes public fields or detect arbitrary memory corruption.
 */
struct ARResult_t
{
    AR_PUBLIC bool ok;
    AR_PUBLIC uint64_t error;
};

/**
 * @brief Creates a successful Result.
 *
 * Constructs the canonical successful Result state.
 *
 * The returned Result satisfies:
 * - 'ok' is true;
 * - 'error' is AR_ERROR_NONE (numeric value zero);
 *
 * @return A valid successful Result.
 */
AR_API ARResult ar_result_success(void);

/**
 * @brief Creates a failed Result.
 *
 * Constructs a failed Result from 'error'.
 *
 * @param[in] error Packed error value describing the cause of failure.
 *
 * @return A valid failed Result containing 'error'.
 *
 * @post The returned Result satisfies:
 *       - 'ok' is false;
 *       - 'error' equals the supplied packed error value;
 * 
 * @attention 'error' must be nonzero.
 *
 * @attention An error value violating these requirements is a programming
 *            error. The constructor invokes assert and aborts program execution;
 *            it does not return an invalid Result. This applies in debug builds.
 */
AR_API ARResult ar_result_failure(uint64_t error);

AR_EXTERN_C_END

#endif /* AR_RESULT_H_ */
