/*
 * Copyright 2026 Nelson Somé
 *
 * Licensed under the Apache License, Version 2.0.
 * See the LICENCE file in the project root for license information.
 */

#include "assertion.h"

#include <stdio.h>
#include <stdlib.h>

AR_NORETURN void ar_assert_fail(
    const char* expr,
    const char* message,
    const char* file,
    int line
) {
    if (message != NULL) {
        fprintf(stderr, "AngryRocketCore: Assertion failed: (%s) --- %s\n  at %s:%d\n",
                expr, message, file, line);
    } else {
        fprintf(stderr, "AngryRocketCore: Assertion failed: (%s)\n  at %s:%d\n",
                expr, file, line);
    }
    fflush(stderr);

    AR_DEBUG_BREAK();
    abort();
}
