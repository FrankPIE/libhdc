cmake_minimum_required(VERSION 3.10.3)

set(SRC_DIR ${CONCRETE_PROJECT_ROOT_DIRECTORY}src)

concrete_source_directory_analyse(
    HDC ${SRC_DIR} 
    EXT h c asm
)

concrete_sources_list(
    HDC_SOURCES
        SOURCES
            ${HDC_ROOT_SOURCES}
)

# common source group
concrete_sources_list(
    HDC_COMMON_SOURCE_LIST
        SOURCES
            ${HDC_COMMON_SOURCES}
        SOURCES_FOLDER
            ${HDC_COMMON_DIR_NAME}
        MSVC_SOURCES 
            ${HDC_COMMON_WINDOWS_SOURCES}
        MSVC_SOURCES_FOLDER
            ${HDC_COMMON_WINDOWS_DIR_NAME}
)

# cpuid source group
concrete_sources_list(
    HDC_CPUID_SOURCE_LIST
        SOURCES 
            ${HDC_CPUID_SOURCES}
        SOURCES_FOLDER
            ${HDC_CPUID_DIR_NAME}
        MSVC_SOURCES 
            ${HDC_CPUID_WINDOWS_MASM_SOURCES}
        MSVC_SOURCES_FOLDER
            ${HDC_CPUID_WINDOWS_MASM_DIR_NAME}
)

# smbios source group
concrete_sources_list(
    HDC_SMBIOS_SOURCE_LIST
        SOURCES 
            ${HDC_SMBIOS_SOURCES}
        SOURCES_FOLDER
            ${HDC_SMBIOS_DIR_NAME}
        MSVC_SOURCES 
            ${HDC_SMBIOS_WINDOWS_SOURCES}
        MSVC_SOURCES_FOLDER
            ${HDC_SMBIOS_WINDOWS_DIR_NAME}
)

concrete_target(     
    libhdc "Shared"

    SOURCES
        ${HDC_SOURCES}
        ${HDC_COMMON_SOURCE_LIST}
        ${HDC_CPUID_SOURCE_LIST}
        ${HDC_SMBIOS_SOURCE_LIST}

    INCLUDE_DIRECTORIES
        PUBLIC ${SRC_DIR}
)

if(MSVC) 
    set(flags "/Fo$(IntDir)cpuid.asm.obj")

    if (${CONCRETE_PROJECT_COMPILER_TARGET} STREQUAL "x86")
        string(APPEND flags " /safeseh")
    endif()

    set_source_files_properties(        
        ${SRC_DIR}/cpuid/windows/masm/cpuid.asm
        PROPERTIES COMPILE_FLAGS ${flags}
    )
endif(MSVC)