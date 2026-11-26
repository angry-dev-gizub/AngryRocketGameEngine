#--------------------------------------------------------------------
# AngryRocketCore
#--------------------------------------------------------------------
add_library(
    AngryRocketCore
    STATIC
    assertion.c
)

target_include_directories(
    AngryRocketCore
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    AngryRocketCore
    PRIVATE
    AngryRocketSanitizers
)