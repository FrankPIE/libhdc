cmake_minimum_required(VERSION 3.10.3)

concrete_target(
    HDCExampleInterface "Interface"

    LINK_LIBRARIES 
        INTERFACE
            libhdc
)

concrete_target(
    HDCExample "Execute"

    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c

    LINK_LIBRARIES
        PRIVATE
            HDCExampleInterface
)