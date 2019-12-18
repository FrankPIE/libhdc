CMAKE_MINIMUM_REQUIRED(VERSION 3.10.3)

SET(SRC_DIR ${CONCRETE_PROJECT_ROOT_DIRECTORY}src)

# common source group
CONCRETE_METHOD_SOURCE_LIST(
    HDC_COMMON_SOURCES
        MSVC_SOURCES 
            ${SRC_DIR}/common/windows/com_ptr.h
        MSVC_SOURCES_FOLDER
            "common\\windows"
)

# cpuid source group
CONCRETE_METHOD_SOURCE_LIST(
    HDC_CPUID_SOURCES
        SOURCES 
            ${SRC_DIR}/cpuid/cpuid.h
            ${SRC_DIR}/cpuid/cpuid.c
            ${SRC_DIR}/cpuid/cpuid_amd_impl.c
            ${SRC_DIR}/cpuid/cpuid_intel_impl.c
        SOURCES_FOLDER
            "cpuid"
        MSVC_SOURCES 
            ${SRC_DIR}/cpuid/windows/masm/cpuid.asm
        MSVC_SOURCES_FOLDER
            "cpuid\\windows"
)

# smbios source group
CONCRETE_METHOD_SOURCE_LIST(
    HDC_SMBIOS_SOURCES
        SOURCES 
            ${SRC_DIR}/smbios/smbios_type.h
            ${SRC_DIR}/smbios/smbios_table.h
        SOURCES_FOLDER
            "smbios"
        MSVC_SOURCES 
            ${SRC_DIR}/smbios/windows/smbios_table.c
        MSVC_SOURCES_FOLDER
            "smbios\\windows"
)

CONCRETE_METHOD_ADD_TARGET(
    TARGET_NAME 
        libhdc
    TYPE        
        "Static"
    SOURCES
        ${HDC_COMMON_SOURCES}
        ${HDC_CPUID_SOURCES}
        ${HDC_SMBIOS_SOURCES}
    INCLUDE_DIRECTORIES
        PRIVATE
            ${HDC_COMMON_SOURCES}
            ${HDC_CPUID_SOURCES}
            ${HDC_SMBIOS_SOURCES}
        PUBLIC
            ${SRC_DIR}
)

IF(MSVC)
    SET_SOURCE_FILES_PROPERTIES(
        ${HDC_CPUID_SOURCES_MSVC}
        PROPERTIES
            COMPILE_FLAGS "/safeseh /Fo$(IntDir)cpuid.asm.obj"
    )
ENDIF(MSVC)