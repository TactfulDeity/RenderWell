cmake_minimum_required(VERSION 3.27.6)

project(RenderWell
  VERSION 0.0.1
  DESCRIPTION "PageOasis EBook Backend"
  HOMEPAGE_URL "https://github.com/TactfulDeity/RenderWell"
  LANGUAGES CXX
)

set(RENDERWELL_BIN_DIR ${RenderWell_BINARY_DIR}/bin)
set(RENDERWELL_GENERATED_DIR ${RenderWell_BINARY_DIR}/generated)
set(RENDERWELL_GENERATED_HEADER_DIR ${RenderWell_BINARY_DIR}/generated/RenderWell)
set(RENDERWELL_DATA_DIR ${RenderWell_BINARY_DIR}/data)
set(RENDERWELL_TEMP_DIR ${RenderWell_BINARY_DIR}/data/temp)
set(RENDERWELL_SYS_DATA_DIR ${RenderWell_BINARY_DIR}/data/system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# -----------------------------------------------------------------------
# Find dependent libraries
# -----------------------------------------------------------------------
find_library(poppler poppler-cpp)

add_library(RenderWell SHARED)
add_library(RenderWell::RenderWell ALIAS RenderWell)

target_compile_features(RenderWell
  PUBLIC
    cxx_std_17
)

if(MSVC)
  target_compile_options(RenderWell
    PRIVATE
      /MP
  )
endif()

if(UNIX)
  target_link_libraries(RenderWell
    PRIVATE
      ${CMAKE_DL_LIBS}
  )
endif()

target_link_libraries(RenderWell PUBLIC "${poppler}")

option(RENDERWELL_ENABLE_LINK_FILESYSTEM "Enables linking to a C++ filesystem library" OFF)
if(RENDERWELL_ENABLE_LINK_FILESYSTEM)
    set(RENDERWELL_FILESYSTEM_LIB "stdc++fs" CACHE STRING "C++ filesystem library to link to")
    set_property(CACHE RENDERWELL_FILESYSTEM_LIB PROPERTY STRINGS "stdc++fs" "c++fs")
    target_link_libraries(RenderWell
            PUBLIC
            ${RENDERWELL_FILESYSTEM_LIB}
    )
endif()

include(GenerateExportHeader)
generate_export_header(RenderWell
        EXPORT_FILE_NAME ${RENDERWELL_GENERATED_HEADER_DIR}/render_well_export.hpp
)

set(RENDERWELL_SOURCE_DIR ${RenderWell_SOURCE_DIR}/src/RenderWell)

set(RENDERWELL_GENERATED_HEADERS
    ${RENDERWELL_GENERATED_HEADER_DIR}/render_well_export.hpp
)

set(RENDERWELL_HEADERS
    ${RENDERWELL_SOURCE_DIR}/BackendManager.hpp
    ${RENDERWELL_SOURCE_DIR}/DataBase.hpp
    ${RENDERWELL_SOURCE_DIR}/EBook.hpp
    ${RENDERWELL_SOURCE_DIR}/json.hpp
    ${RENDERWELL_SOURCE_DIR}/List.hpp
    ${RENDERWELL_SOURCE_DIR}/ListManager.hpp
    ${RENDERWELL_SOURCE_DIR}/DataObject.hpp
    ${RENDERWELL_SOURCE_DIR}/Renderer.hpp
    ${RENDERWELL_SOURCE_DIR}/Settings.hpp
    ${RENDERWELL_SOURCE_DIR}/Sorter.hpp
    ${RENDERWELL_SOURCE_DIR}/Types.hpp
)

set(RENDERWELL_SRCS
    ${RENDERWELL_SOURCE_DIR}/BackendManager.cpp
    ${RENDERWELL_SOURCE_DIR}/DataBase.cpp
    ${RENDERWELL_SOURCE_DIR}/ListManager.cpp
    ${RENDERWELL_SOURCE_DIR}/Renderer.cpp
    ${RENDERWELL_SOURCE_DIR}/Settings.cpp
)

configure_file(${RenderWell_SOURCE_DIR}/cmake/render_well_directories.hpp.in ${RENDERWELL_GENERATED_HEADER_DIR}/render_well_directories.hpp)

target_sources(RenderWell
        PRIVATE
        ${RENDERWELL_GENERATED_HEADERS}
        ${RENDERWELL_HEADERS}
        ${RENDERWELL_SRCS}
)

source_group(TREE ${RENDERWELL_SOURCE_DIR} PREFIX "RenderWell" FILES ${RENDERWELL_HDRS})
source_group(TREE ${RENDERWELL_GENERATED_HEADER_DIR} PREFIX "RenderWell/generated" FILES ${RENDERWELL_GENERATED_HEADERS})
source_group(TREE ${RENDERWELL_SOURCE_DIR} PREFIX "RenderWell" FILES ${RENDERWELL_SRCS})

set(RENDERWELL_INCLUDE_DIR ${RenderWell_SOURCE_DIR}/src)

target_include_directories(RenderWell
        PUBLIC
        $<BUILD_INTERFACE:${RENDERWELL_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${RENDERWELL_GENERATED_DIR}>
        $<INSTALL_INTERFACE:include>
)

# ------------------------------------------------------------------------------
# CLI Executable
# ------------------------------------------------------------------------------
#add_subdirectory(${RenderWell_SOURCE_DIR}/src/Sweep)

# ------------------------------------------------------------------------------
# Testing
# ------------------------------------------------------------------------------
option(RENDERWELL_BUILD_TESTS "Enable building RENDERWELL tests" ON)
if(RENDERWELL_BUILD_TESTS)
    include(CTest)
    add_subdirectory(test)
endif()

# ------------------------------------------------------------------------------
# Packaging
# ------------------------------------------------------------------------------
set(RENDERWELL_PACKAGE_NAMESPACE "RenderWell::")

option(RENDERWELL_ENABLE_PACKAGING "Enables RENDERWELL packaging" ON)
if(RENDERWELL_ENABLE_PACKAGING)
  if(WIN32)
    set(CPACK_GENERATOR ZIP)
  else()
    set(CPACK_GENERATOR TGZ)
  endif()
  include(CPack)
endif()
