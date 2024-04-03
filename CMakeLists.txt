cmake_minimum_required(VERSION 3.5)
project(cccompression VERSION 0.0.1)

include(cmake/ClangFormat.cmake)
include(cmake/Cppcheck.cmake)
include(cmake/Doxygen.cmake)
include(cmake/PVS-Studio.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ALL_SOURCES
    cccompression/algorithms/frequency_table.cpp
    cccompression/algorithms/frequency_table.hpp
    cccompression/algorithms/huffman_tree.hpp
)

if (NOT DISABLE_BUILDING_EXECUTABLE)
    add_executable(${PROJECT_NAME} ${ALL_SOURCES} cccompression/main.cpp)

    # -- Boost
    # Please, do not remove the magic trick below
    # It will broke the CI/CD
    find_package(Boost 1.74 REQUIRED COMPONENTS program_options)

    target_include_directories(${PROJECT_NAME} PRIVATE .)
    if (TARGET Boost::boost)
        target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)
        target_link_libraries(${PROJECT_NAME} PUBLIC Boost::program_options)
    else()
        target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})
    endif()

    configure_file(cccompression/config.hpp.in config.hpp @ONLY)
    include_directories(${CMAKE_CURRENT_BINARY_DIR})
    install(TARGETS ${PROJECT_NAME})
endif()

add_clang_format_target()
add_cppcheck_target()
add_pvs_studio_target()
add_docs_target()