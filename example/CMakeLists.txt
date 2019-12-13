CMAKE_MINIMUM_REQUIRED(VERSION 3.10.3)

CONCRETE_METHOD_ADD_TARGET(
    TARGET_NAME 
        HardwareCollect
    TYPE        
        "Execute"
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    LINK_LIBRARIES
        PRIVATE
            $<TARGET_NAME:libhdc>
)