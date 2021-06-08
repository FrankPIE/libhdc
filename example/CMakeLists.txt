cmake_minimum_required(VERSION 3.10.3)

concrete_target(
    HDCExampleInterface "Interface"

    LINK_LIBRARIES 
        INTERFACE
            libhdc
)

concrete_target(
    SMBIOS "Execute"

    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/simbios_example/main.c

    LINK_LIBRARIES
        PRIVATE
            HDCExampleInterface
)

concrete_target(
    HashMap "Execute"

    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/hashmap_example/main.c
    LINK_LIBRARIES
        PRIVATE
            HDCExampleInterface
)

concrete_target(
    CPUID "Execute"
    
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/cpuid_example/main.c
    LINK_LIBRARIES
        PRIVATE
            HDCExampleInterface
)