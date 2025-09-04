cmake_minimum_required(VERSION 3.26)

project(cpp23_starter
  VERSION 0.1.0
  DESCRIPTION "Minimal C++23 + CMake starter"
  LANGUAGES CXX
)

# --- Defaults
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build options
option(BUILD_TESTING "Build tests" ON)
option(ENABLE_ASAN "Enable AddressSanitizer (Debug only)" ON)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer (Debug only)" ON)
option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

# Output dirs (nice & tidy)
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")

# Warnings & sanitizers helper
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(SanitizeAndWarnings)

# --- Library
add_library(hello_lib
  src/hello.cpp
)
target_include_directories(hello_lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(hello_lib PUBLIC cxx_std_23)
apply_project_warnings(hello_lib ${WARNINGS_AS_ERRORS})
apply_sanitizers(hello_lib ${ENABLE_ASAN} ${ENABLE_UBSAN})

# --- Executable
add_executable(cpp23_starter src/main.cpp)
target_link_libraries(cpp23_starter PRIVATE hello_lib)
apply_project_warnings(cpp23_starter ${WARNINGS_AS_ERRORS})
apply_sanitizers(cpp23_starter ${ENABLE_ASAN} ${ENABLE_UBSAN})

# --- Tests (GoogleTest via FetchContent)
if(BUILD_TESTING)
  include(CTest)
  enable_testing()

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )
  # For MSVC runtime selection behavior
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  add_executable(hello_test tests/hello_test.cpp)
  target_link_libraries(hello_test PRIVATE hello_lib GTest::gtest_main)
  apply_project_warnings(hello_test ${WARNINGS_AS_ERRORS})
  apply_sanitizers(hello_test ${ENABLE_ASAN} ${ENABLE_UBSAN})

  include(GoogleTest)
  gtest_discover_tests(hello_test)
endif()

