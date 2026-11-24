option(
    AR_ENABLE_SANITIZERS
    "Enable sanitizers in debug builds"
    ON # on by default.
)

add_library(ar-sanitizers INTERFACE)

if(AR_ENABLE_SANITIZERS)

    if(
        CMAKE_C_COMPILER_ID MATCHES "GNU|Clang"
        AND
        CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang"
    )

        target_compile_options(
            ar-sanitizers
            INTERFACE
            $<$<CONFIG:Debug>:-fsanitize=address,undefined>
            $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        )

        target_link_options(
            ar-sanitizers
            INTERFACE
            $<$<CONFIG:Debug>:-fsanitize=address,undefined>
        )

    elseif(MSVC)

        target_compile_options(
            ar-sanitizers
            INTERFACE
            $<$<CONFIG:Debug>:/fsanitize=address>
        )

    else()
    message(
        WARNING
        "Sanitizers are not configured for compiler: ${CMAKE_C_COMPILER_ID}"
    )

    endif()

endif()