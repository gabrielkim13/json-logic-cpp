cmake_minimum_required(VERSION 3.18)
project(jsonlogic VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Set a default build type if none was specified
set(default_build_type "Release")

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -O3 -g")

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(default_build_type "Debug")
    add_compile_definitions(DBUG)
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)

    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include_directories(src)

try_compile(HAVE_EXECUTION ${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src/executiontest.cpp)
if(NOT HAVE_EXECUTION)
        message(FATAL_ERROR "Compiler seems to be old, unable to compile this source")
endif()

# Compile all sources into object files to avoid double compiling for static and dynamic libraries
add_library(objlib OBJECT 
        src/json_logic.cpp
        src/operations/array/all.cpp
        src/operations/array/filter.cpp
        src/operations/array/in.cpp
        src/operations/array/map.cpp
        src/operations/array/merge.cpp
        src/operations/array/none.cpp
        src/operations/array/reduce.cpp
        src/operations/array/some.cpp
        src/operations/data/missing.cpp
        src/operations/data/missing_some.cpp
        src/operations/data/var.cpp
        src/operations/logic/and.cpp
        src/operations/logic/different.cpp
        src/operations/logic/equal.cpp
        src/operations/logic/if.cpp
        src/operations/logic/not.cpp
        src/operations/logic/or.cpp
        src/operations/logic/truthy.cpp
        src/operations/misc/log.cpp
        src/operations/numeric/addition.cpp
        src/operations/numeric/division.cpp
        src/operations/numeric/gt.cpp
        src/operations/numeric/gte.cpp
        src/operations/numeric/lt.cpp
        src/operations/numeric/lte.cpp
        src/operations/numeric/max.cpp
        src/operations/numeric/min.cpp
        src/operations/numeric/modulo.cpp
        src/operations/numeric/multiplication.cpp
        src/operations/numeric/subtraction.cpp
        src/operations/string/cat.cpp
        src/operations/string/substr.cpp
)

# shared libraries need PIC
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

# Compile shared and static versions of library
add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:objlib>)
add_library(${PROJECT_NAME}-static STATIC $<TARGET_OBJECTS:objlib>)
set_target_properties(${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

find_package(nlohmann_json 3.9.1 REQUIRED)

target_link_libraries(${PROJECT_NAME}-static PRIVATE nlohmann_json::nlohmann_json)
add_library(jsonlogic::jsonlogic ALIAS jsonlogic-static)

target_include_directories(
  ${PROJECT_NAME}-static
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/lib/json/include/nlohmann/>
)

if(NOT DISABLE_TESTS)
    add_subdirectory(test)
endif()

install(TARGETS ${PROJECT_NAME}
    COMPONENT Library
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}

)

install(TARGETS ${PROJECT_NAME}-static
    COMPONENT Devel
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(FILES src/json_logic.h src/jsonlogic/exception.h 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/jsonlogic
    COMPONENT Devel
)

include(cpack.cmake)
include(CPack)