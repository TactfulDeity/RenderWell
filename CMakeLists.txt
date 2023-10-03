cmake_minimum_required(VERSION 3.20)

project(RenderWell
  VERSION 0.0.1
  DESCRIPTION "PageOasis EBook Backend"
  HOMEPAGE_URL "https://github.com/TactfulDeity/RenderWell"
  LANGUAGES CXX
)

set(RENDERWELL_BIN_DIR ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# -----------------------------------------------------------------------
# Find dependent libraries
# -----------------------------------------------------------------------
# find_package(fmt CONFIG REQUIRED)

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

target_link_libraries(RenderWell
  PUBLIC
)

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

set(RENDERWELL_HEADERS
    ${RENDERWELL_SOURCE_DIR}/BackendManager.hpp
    ${RENDERWELL_SOURCE_DIR}/EBook.hpp
    ${RENDERWELL_SOURCE_DIR}/List.hpp
    ${RENDERWELL_SOURCE_DIR}/ListManager.hpp
    ${RENDERWELL_SOURCE_DIR}/Renderer.hpp
    ${RENDERWELL_SOURCE_DIR}/Settings.hpp
    ${RENDERWELL_SOURCE_DIR}/Sorter.hpp
    ${RENDERWELL_SOURCE_DIR}/Types.hpp
)

set(RENDERWELL_SRCS
    ${RENDERWELL_SOURCE_DIR}/BackendManager.cpp
    # ${RENDERWELL_SOURCE_DIR}/EBook.cpp
    # ${RENDERWELL_SOURCE_DIR}/List.cpp
    ${RENDERWELL_SOURCE_DIR}/ListManager.cpp
    ${RENDERWELL_SOURCE_DIR}/Renderer.cpp
    ${RENDERWELL_SOURCE_DIR}/Settings.cpp
)

target_sources(RenderWell
        PRIVATE
        ${RENDERWELL_HEADERS}
        ${RENDERWELL_SRCS}
)

source_group(TREE ${RENDERWELL_SOURCE_DIR} PREFIX "complex" FILES ${RENDERWELL_HDRS})
source_group(TREE ${RENDERWELL_GENERATED_HEADER_DIR} PREFIX "complex/generated" FILES ${RENDERWELL_GENERATED_HEADERS})
source_group(TREE ${RENDERWELL_SOURCE_DIR} PREFIX "complex" FILES ${RENDERWELL_SRCS})

set(RENDERWELL_INCLUDE_DIR ${complex_SOURCE_DIR}/src)

target_include_directories(RenderWell
        PUBLIC
        $<BUILD_INTERFACE:${RENDERWELL_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${RENDERWELL_GENERATED_DIR}>
        $<INSTALL_INTERFACE:include>
)

#if(RENDERWELL_BUILD_TESTS)
#    include(CTest)
#    add_subdirectory(test)
#endif()
