cmake_minimum_required(VERSION 3.10.3)

concrete_target(
    TARGET_NAME
        HDCExampleInterface
    TYPE        
        "Interface"
    LINK_LIBRARIES
        INTERFACE
            libhdc
)

concrete_target(
    TARGET_NAME 
        SMBIOS
    TYPE        
        "Execute"
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/simbios_example/main.c
    LINK_LIBRARIES
        PRIVATE
            HDCExampleInterface
)

concrete_target(
    TARGET_NAME 
        HashMap
    TYPE        
        "Execute"
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/hashmap_example/main.c
    LINK_LIBRARIES
        PRIVATE
            HDCExampleInterface
)

concrete_target(
    TARGET_NAME 
        CPUID
    TYPE        
        "Execute"
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/cpuid_example/main.c
    LINK_LIBRARIES
        PRIVATE
            HDCExampleInterface
)