/*
 * Copyright 2026 Nelson Somé
 *
 * Licensed under the Apache License, Version 2.0.
 * See the LICENCE file in the project root for license information.
 */

#include "assertion.h"
#include "errors.h"
#include "result.h"

ARResult arResultSuccess(void)
{
    return (ARResult) {
        .ok = true,
        .error = AR_ERROR_NONE,
    };
}

ARResult arResultFailure(uint64_t error)
{
    AR_ASSERT_MSG(error != AR_ERROR_NONE, "AngryRocketCore: 'error' must be non-zero.");

    return (ARResult) {
        .ok = false,
        .error = error,
    };
}
