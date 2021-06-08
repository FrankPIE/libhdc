# REQUIRE LEAST CMAKE 3.10.3
cmake_minimum_required(VERSION 3.10.3)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_HOME_DIRECTORY}/cmake/Concrete/modules)

include(Concrete)

project(${CONCRETE_PROJECT_DEFAULT_PARAMETER})

concrete_project(
    libhdc
    VERSION      1 1 0 0
    DESCRIPTION  "hardware information collect library"
    HOMEPAGE_URL "https://github.com/FrankPIE/SMBIOS"
    LANGUAGES    C ASM_MASM

    CONFIGURATION_TYPES Debug Release

    ROOT_DIR            ${CMAKE_HOME_DIRECTORY}/
    BINARY_OUTPUT_DIR   ${CMAKE_HOME_DIRECTORY}/bin
    LIBRARY_OUTPUT_DIR  ${CMAKE_HOME_DIRECTORY}/lib
    WITH_COMPILER_TARGET_POSTFIX
)

concrete_option(HDC_PACKAGE_VERBOSE "option for package verbose" ON)

concrete_set_package_manager_properties(
    VERBOSE  ${HDC_PACKAGE_VERBOSE}
    BASE_DIR ${CMAKE_BINARY_DIR}/.3rd
)

concrete_set_global_properties(
    PROPERTIES 
        USE_FOLDERS  ON
        PREDEFINED_TARGETS_FOLDER "CMakeTargets"
)

concrete_global_target_configure(
    INCLUDE_DIRECTORIES ${CMAKE_BINARY_DIR}
    COMPILE_DEFINITIONS $<$<STREQUAL:"${CONCRETE_PROJECT_COMPILER_TARGET}","x64">:MASM64>       
)

concrete_add_subdirectory(
    SOURCE_DIRECTORYS 
        ${CMAKE_HOME_DIRECTORY}/src 
        ${CMAKE_HOME_DIRECTORY}/example
    BINARY_DIRECTORIES
        libhdc.project
        example.project
    FOLDERS
        "Library"
        "Example"
)

concrete_set_vs_startup_project(HDCExample)