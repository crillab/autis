cmake_minimum_required(VERSION 3.14)

project(crillab-autisTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(crillab-autis REQUIRED)
  enable_testing()
endif()

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(crillab-autis_test source/crillab-autis_test.cpp)
target_link_libraries(
    crillab-autis_test PRIVATE
    crillab-autis::crillab-autis
    Catch2::Catch2WithMain
)
target_compile_features(crillab-autis_test PRIVATE cxx_std_20)

catch_discover_tests(crillab-autis_test)

# ---- End-of-file commands ----

add_folders(Test)
