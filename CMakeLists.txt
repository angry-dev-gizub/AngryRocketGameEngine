cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

#--------------------------------------------------------------------
# Version
#--------------------------------------------------------------------

file(
    STRINGS
    "${CMAKE_CURRENT_SOURCE_DIR}/VERSION"
    AR_VERSION
    LIMIT_COUNT 1
)

if (NOT AR_VERSION)
    message(FATAL_ERROR "Failed to read Ar version")
endif()

if (NOT AR_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$")
    message(
        FATAL_ERROR
        "Invalid Ar version '${AR_VERSION}'. Expected MAJOR.MINOR.PATCH.TWEAK"
    )
endif()

#--------------------------------------------------------------------
# Project
#--------------------------------------------------------------------

project(
    AngryRocketGameEngine
    VERSION ${AR_VERSION}
    LANGUAGES C CXX
    DESCRIPTION "The Angry Rocket game engine."
)

#--------------------------------------------------------------------
# Language settings
#--------------------------------------------------------------------

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

#--------------------------------------------------------------------
# Global settings
#--------------------------------------------------------------------

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(AR_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(AR_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

string(
    COMPARE EQUAL
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}"
    AR_STANDALONE
)

#--------------------------------------------------------------------
# Subdirectories
#--------------------------------------------------------------------

add_subdirectory(external)
add_subdirectory(sani)
add_subdirectory(platform)
add_subdirectory(core)

if (${AR_STANDALONE})
    enable_testing()
    add_subdirectory(tests)
endif()
