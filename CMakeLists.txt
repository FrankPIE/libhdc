# REQUIRE LEAST CMAKE 3.10.3
cmake_minimum_required(VERSION 3.10.3)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_HOME_DIRECTORY}/cmake/Concrete/modules)

include(Concrete)

project(${CONCRETE_PROJECT_DEFAULT_PARAMETER})

concrete_project(
    NAME         libhdc
    VERSION      1 1 0
    DESCRIPTION  "hardware information collect library"
    HOMEPAGE_URL "https://github.com/FrankPIE/SMBIOS"
    LANGUAGES    C ASM_MASM

    CONFIGURATION_TYPES Debug Release

    ROOT_DIR            ${CMAKE_HOME_DIRECTORY}/
    BINARY_OUTPUT_DIR   ${CMAKE_HOME_DIRECTORY}/bin
    LIBRARY_OUTPUT_DIR  ${CMAKE_HOME_DIRECTORY}/lib
    WITH_COMPILER_TARGET_SUBDIR
)

concrete_set_global_properties(
    PROPERTIES 
        USE_FOLDERS  ON
        PREDEFINED_TARGETS_FOLDER "CMakeTargets"
)

concrete_global_target_configure(
    INCLUDE_DIRECTORIES 
        ${CMAKE_BINARY_DIR}
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

concrete_set_vs_startup_project(CPUID)