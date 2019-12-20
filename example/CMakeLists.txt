CMAKE_MINIMUM_REQUIRED(VERSION 3.10.3)

CONCRETE_METHOD_ADD_TARGET(
    TARGET_NAME
        HDCExampleInterface
    TYPE        
        "Interface"
    LINK_LIBRARIES
        INTERFACE
            $<TARGET_NAME:libhdc>
)

CONCRETE_METHOD_ADD_TARGET(
    TARGET_NAME 
        SMBIOS
    TYPE        
        "Execute"
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/simbios_example/main.c
    LINK_LIBRARIES
        PRIVATE
            $<TARGET_NAME:HDCExampleInterface>
)

CONCRETE_METHOD_ADD_TARGET(
    TARGET_NAME 
        HashMap
    TYPE        
        "Execute"
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/hashmap_example/main.c
    LINK_LIBRARIES
        PRIVATE
            $<TARGET_NAME:HDCExampleInterface>
)