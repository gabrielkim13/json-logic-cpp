set(CMAKE_CXX_STANDARD 20)

set(TEST_TARGET ${PROJECT_NAME}_test)

add_executable(
        ${TEST_TARGET}

        add_rm_operation.cpp
        operations/array/all.cpp
        operations/array/filter.cpp
        operations/array/in.cpp
        operations/array/map.cpp
        operations/array/merge.cpp
        operations/array/none.cpp
        operations/array/reduce.cpp
        operations/array/some.cpp
        operations/data/missing.cpp
        operations/data/missing_some.cpp
        operations/data/var.cpp
        operations/logic/and.cpp
        operations/logic/different.cpp
        operations/logic/equal.cpp
        operations/logic/if.cpp
        operations/logic/not.cpp
        operations/logic/or.cpp
        operations/logic/truthy.cpp
        operations/misc/log.cpp
        operations/numeric/addition.cpp
        operations/numeric/division.cpp
        operations/numeric/gt.cpp
        operations/numeric/gte.cpp
        operations/numeric/lt.cpp
        operations/numeric/lte.cpp
        operations/numeric/max.cpp
        operations/numeric/min.cpp
        operations/numeric/modulo.cpp
        operations/numeric/multiplication.cpp
        operations/numeric/subtraction.cpp
        operations/string/cat.cpp
        operations/string/substr.cpp
)

add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})

target_include_directories(
        ${TEST_TARGET}

        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}

        PRIVATE ${gmock_SOURCE_DIR}
        PRIVATE ${gmock_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
        PRIVATE ${gtest_SOURCE_DIR}/include
)

target_link_libraries(
        ${TEST_TARGET}

        PUBLIC ${PROJECT_NAME}

        PRIVATE gtest
        PRIVATE gtest_main
)

if (NOT TARGET gtest)
    add_subdirectory(lib/googletest)
endif()
