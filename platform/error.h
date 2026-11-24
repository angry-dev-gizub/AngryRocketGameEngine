/*
 * Copyright 2026 Nelson Somé
 *
 * Licensed under the Apache License, Version 2.0.
 * See the LICENSE file in the project root for license information.
 */

/**
 * @file error.h
 *
 * @author Nelson Somé
 *
 * @brief The PAL's error constants.
 *
 * @note This file is part of Angry Rocket Platform Abstraction Layer.
 */

#ifndef AR_PAL_ERROR_H_
#define AR_PAL_ERROR_H_

#include <stdint.h>

/** Error constants */

#define AR_PAL_ERROR_NONE 0
#define AR_PAL_ERROR_INVALID_ARGUMENT 1

/** Platform abstraction error type. */
typedef uint32_t ARPALError;

#endif /* AR_PAL_ERROR_H_ */
