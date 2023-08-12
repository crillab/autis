cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    crillab-autis
    VERSION 0.1.0
    DESCRIPTION "A library for parsing combinatorial problems"
    HOMEPAGE_URL "https://github.com/crillab/autis"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB")
endif()

find_package(crillab-easyjni REQUIRED)
find_package(crillab-universe REQUIRED)
find_package(crillab-except REQUIRED)
find_package(xcsp3-cpp-parser REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(Iconv REQUIRED)

# ---- Declare library ----

file(GLOB_RECURSE HEADERS
        ${PROJECT_SOURCE_DIR}/include/**.hpp
        )

file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/source/**.cpp
        )

add_library(
    crillab-autis_crillab-autis
    ${HEADERS} ${SOURCES}
)
add_library(crillab-autis::crillab-autis ALIAS crillab-autis_crillab-autis)
target_link_libraries(crillab-autis_crillab-autis crillab-universe::crillab-universe crillab-except::crillab-except xcsp3-cpp-parser::xcsp3-cpp-parser)


if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(crillab-autis_crillab-autis PUBLIC CRILLAB_AUTIS_STATIC_DEFINE)
endif()

set_target_properties(
    crillab-autis_crillab-autis PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME crillab-autis
    OUTPUT_NAME crillab-autis
)

target_include_directories(
    crillab-autis_crillab-autis ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>"
)

target_include_directories(
    crillab-autis_crillab-autis SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(crillab-autis_crillab-autis PUBLIC cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT crillab-autis_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of crillab-autis"
  )
endif()

include(cmake/dev-mode.cmake)
