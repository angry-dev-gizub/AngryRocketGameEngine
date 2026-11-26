/*
 * Copyright 2026 Nelson Somé
 *
 * Licensed under the Apache License, Version 2.0.
 * See the LICENCE file in the project root for license information.
 */

/**
 * @file errors.h
 *
 * @author Nelson Somé
 *
 * @brief Shared layer, source, severity, domain, and error definitions.
 *
 * Defines the symbolic values used to classify errors across Angry Rocket Core.
 * Complete error values are constructed with AR_ERROR_PACK and can be
 * stored in uint64_t.
 *
 * @note This file is part of AngryRocketCore.
 */

#ifndef AR_ERROR_H_
#define AR_ERROR_H_

#include <stdint.h>

/**
 * @brief Packs the layer, source, domain, severity, and error code together
 *        into one 64-bit integer.
 *
 * @param[in] layer Integer layer identifier, expected to be in the range 0 to 255.
 * @param[in] source Integer source identifier, expected to be in the range 0 to 255.
 * @param[in] domain Integer domain identifier, expected to be in the range 0 to 255.
 * @param[in] severity Integer severity identifier, expected to be in the range 0 to 255.
 * @param[in] code Integer code within the domain, expected to be in the range 0 to UINT32_MAX.
 *
 * @return The packed error value, with the layout 0xLLSSDDXXCCCCCCCC (XX = severity bits).
 *
 * @note Each argument is evaluated exactly once. Values outside their
 *       allocated bit widths are truncated by masking. Callers must provide
 *       valid identifiers.
 */
#define AR_ERROR_PACK(layer, source, domain, severity, code)\
    (\
    (((uint64_t)(layer)    & 0xFFULL) << 56U)  |\
    (((uint64_t)(source)   & 0xFFULL) << 48U)   |\
    (((uint64_t)(domain)   & 0xFFULL) << 40U)   |\
    (((uint64_t)(severity) & 0xFFULL) << 32U)   |\
    (((uint64_t)(code)     & 0xFFFFFFFFULL))

/**
 * @brief Extracts the layer field from a complete packed error value.
 *
 * @param[in] error Complete packed error value with numeric layout 0xLLSSDDXXCCCCCCCC.
 * @return The value of bits 56 through 63, converted to uint8_t.
 *
 * @note The argument is evaluated once. No validity or identifier-recognition
 *       check is performed. All other fields are ignored.
 *       With an integer constant-expression argument, the result is an integer
 *       constant expression. Extracting from zero returns zero.
 */
#define AR_ERROR_GET_LAYER(error)\
    ((uint8_t)(((uint64_t)(error) >> 56U) & 0xFFULL))

/**
 * @brief Extracts the source field from a complete packed error value.
 *
 * @param[in] error Complete packed error value with numeric layout 0xLLSSDDXXCCCCCCCC.
 * @return The value of bits 48 through 55, converted to uint8_t.
 *
 * @note The argument is evaluated once. No validity or identifier-recognition
 *       check is performed. All other fields are ignored.
 *       With an integer constant-expression argument, the result is an integer
 *       constant expression. Extracting from zero returns zero.
 */
#define AR_ERROR_GET_SOURCE(error)\
    ((uint8_t)(((uint64_t)(error) >> 48U) & 0xFFULL))

/**
 * @brief Extracts the domain field from a complete packed error value.
 *
 * @param[in] error Complete packed error value with numeric layout 0xLLSSDDXXCCCCCCCC.
 * @return The value of bits 40 through 47, converted to uint8_t.
 *
 * @note The argument is evaluated once. No validity or identifier-recognition
 *       check is performed. All other fields are ignored.
 *       With an integer constant-expression argument, the result is an integer
 *       constant expression. Extracting from zero returns zero.
 */
#define AR_ERROR_GET_DOMAIN(error)\
    ((uint8_t)(((uint64_t)(error) >> 40U) & 0xFFULL))

/**
 * @brief Extracts the severity field from a complete packed error value.
 *
 * @param[in] error Complete packed error value with numeric layout 0xLLSSDDXXCCCCCCCC.
 * @return The value of bits 32 through 39, converted to uint8_t.
 *
 * @note The argument is evaluated once. No validity or identifier-recognition
 *       check is performed. All other fields are ignored.
 *       With an integer constant-expression argument, the result is an integer
 *       constant expression. Extracting from zero returns zero.
 */
#define AR_ERROR_GET_SEVERITY(error)\
    ((uint8_t)(((uint64_t)(error) >> 32U) & 0xFFULL))

/**
 * @brief Extracts the code field from a complete packed error value.
 *
 * @param[in] error Complete packed error value with numeric layout 0xLLSSDDXXCCCCCCCC.
 * @return The value of bits 0 through 31, converted to uint32_t.
 *
 * @note The argument is evaluated once. No validity or identifier-recognition
 *       check is performed. All other fields are ignored.
 *       With an integer constant-expression argument, the result is an integer
 *       constant expression. Extracting from zero returns zero.
 */
#define AR_ERROR_GET_CODE(error)\
    ((uint32_t)(((uint64_t)(error)) & 0xFFFFFFFFULL))

/**
 * @brief Layer identifiers used to identify the architectural layer
 *        in which an error originated.
 *
 * A layer identifies the architectural part of Angry Rocket responsible
 * for originating an error. It describes the error's architectural origin,
 * not necessarily the component that ultimately reports or handles it.
 *
 * Examples of architectural layers include:
 * - Core
 * - Platform
 * - Runtime
 * - Other architectural layers introduced in the future.
 *
 * Layer identifiers are individual values and must not be combined as flags.
 *
 * @note All layer identifiers must be globally defined constants. They must
 *       be centrally declared in this file to prevent conflicting definitions
 *       and ensure consistent identification across the engine.
 *
 * @note New layer identifiers should be added here as the architecture evolves.
 */

#define AR_ERROR_LAYER_COMMON   ((uint8_t)0U) /**< Errors shared across layers. */
#define AR_ERROR_LAYER_PLATFORM ((uint8_t)1U) /**< Errors from the platform layer. */
#define AR_ERROR_LAYER_CORE     ((uint8_t)2U) /**< Errors from the core layer. */

/**
 * @brief Source identifiers used to identify the provider or component
 *        that defines an error-code namespace.
 *
 * A source identifies the origin of an error-code definition. It distinguishes
 * between different providers that may define their own error codes, even
 * when those providers belong to the same architectural layer.
 *
 * Sources may represent platform APIs, external libraries, engine components,
 * or plugins.
 *
 * Examples of possible sources include:
 * - Windows
 * - POSIX
 * - GLFW or Other external libraries
 * - Plugin Manager
 * - Asset Manager
 * - Resource Manager
 * - Other internal or external components.
 *
 * Source identifiers are individual values and must not be combined as flags.
 *
 * @note All source identifiers must be globally defined constants. Each
 *       source must have a unique identifier that is consistently used
 *       throughout the engine.
 *
 * @note Internal components and plugins must use globally defined source
 *       identifiers when they introduce independent error-code namespaces.
 *       Components that share an existing error-code namespace do not need
 *       separate source identifiers.
 */

/** Errors defined by Angry Rocket itself rather than an external provider. */
#define AR_ERROR_SOURCE_COMMON ((uint8_t)0U)

/**
 * @brief Domain identifiers used to group error codes.
 *
 * A domain identifies the group or subsystem in which a code is defined. The
 * same code number may be used in different domains without referring to the
 * same error.
 *
 * Domain identifiers are individual values and must not be combined as flags.
 *
 * @note Common errors may be returned by multiple subsystems. Their domain
 *       identifies the shared definition, not the subsystem that returned it.
 *
 * @note Every subsystem must define its own error domain when it introduces
 *       an independent group of error codes.
 *
 * @note Domain identifiers must be globally defined constants. Each
 *       subsystem must declare its domain identifier in its public header
 *       so that the identifier is consistently available throughout the
 *       engine. Domain identifiers must not be defined locally or assigned
 *       independently by individual source files.
 */

/** Errors shared across subsystems. */
#define AR_ERROR_DOMAIN_COMMON ((uint8_t)0U)

/**
 * @brief Severity identifiers used to classify reported conditions.
 *
 * Severity identifiers occupy the severity field of a packed value. They are
 * individual values, not flags, and must not be combined using bitwise OR.
 *
 * @attention Severity alone does not document the validity of an operation's
 *            outputs. Each operation must specify its success and failure
 *            conditions, valid outputs, and whether processing may continue.
 *
 * @note A severity constant does not emit a message, terminate the process,
 *       or perform recovery. Those actions belong to the consuming code.
 *
 * @note Plugins may define additional severity levels, but they must also
 *       provide appropriate error-handling strategies for those levels.
 *
 * @note Severity identifiers must be globally defined constants so that
 *       their meaning remains consistent throughout the engine.
 */

#define AR_ERROR_SEVERITY_NONE    ((uint8_t)0U) /**< No severity assigned. */
#define AR_ERROR_SEVERITY_LOG     ((uint8_t)1U) /**< Informational condition. */
#define AR_ERROR_SEVERITY_WARNING ((uint8_t)2U) /**< Warning condition. */
#define AR_ERROR_SEVERITY_ERROR   ((uint8_t)3U) /**< Error condition. */
#define AR_ERROR_SEVERITY_FATAL   ((uint8_t)4U) /**< Condition classified as fatal. */

/**
 * @brief Error values shared across Angry Rocket Core subsystems.
 *
 * AR_ERROR_NONE has numeric value zero and represents the absence of an error.
 * Compare complete packed values when identifying a specific constant.
 *
 * @note Shared error definitions must be globally defined constants so that
 *       their meaning and numeric representation remain consistent across
 *       all subsystems.
 */

#define AR_ERROR_NONE                  AR_ERROR_PACK(AR_ERROR_LAYER_COMMON, AR_ERROR_SOURCE_COMMON, AR_ERROR_DOMAIN_COMMON, AR_ERROR_SEVERITY_NONE,  0U)  /**< No error. */
#define AR_ERROR_UNKNOWN               AR_ERROR_PACK(AR_ERROR_LAYER_COMMON, AR_ERROR_SOURCE_COMMON, AR_ERROR_DOMAIN_COMMON, AR_ERROR_SEVERITY_ERROR, 1U)  /**< Unknown failure. */
#define AR_ERROR_INVALID_ARGUMENT      AR_ERROR_PACK(AR_ERROR_LAYER_COMMON, AR_ERROR_SOURCE_COMMON, AR_ERROR_DOMAIN_COMMON, AR_ERROR_SEVERITY_ERROR, 2U)  /**< An argument does not satisfy the operation's requirements. */
#define AR_ERROR_UNSUPPORTED_OPERATION AR_ERROR_PACK(AR_ERROR_LAYER_COMMON, AR_ERROR_SOURCE_COMMON, AR_ERROR_DOMAIN_COMMON, AR_ERROR_SEVERITY_ERROR, 3U)  /**< Unsupported operation. */
#define AR_ERROR_INVALID_DESCRIPTOR    AR_ERROR_PACK(AR_ERROR_LAYER_COMMON, AR_ERROR_SOURCE_COMMON, AR_ERROR_DOMAIN_COMMON, AR_ERROR_SEVERITY_ERROR, 4U)  /**< Invalid descriptor. */

#endif /* AR_ERROR_H_ */
