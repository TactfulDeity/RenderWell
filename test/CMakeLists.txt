file(TO_CMAKE_PATH "${PROJECT_SOURCE_DIR}" RENDERWELL_SOURCE_DIR_NORM)
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}" RENDERWELL_BINARY_DIR_NORM)

set(RENDERWELL_TEST_DIRS_HEADER ${RENDERWELL_GENERATED_HEADER_DIR}/UnitTest/render_well_test_dirs.hpp)

configure_file(${RenderWell_SOURCE_DIR}/test/render_well_test_dirs.hpp.in ${RENDERWELL_TEST_DIRS_HEADER} @ONLY)

find_package(Catch2 CONFIG REQUIRED)

include(Catch)

add_executable(RenderWell_test
  ${RENDERWELL_TEST_DIRS_HEADER}
  RenderWell_test_main.cpp
  TC3.cpp
  TC10.cpp
  TC11.cpp
  TC12.cpp
  TC13.cpp
  TC14.cpp
  TC15.cpp
  TC16.cpp
  TC18.cpp
  TC19.cpp
  TC23.cpp
)

target_link_libraries(RenderWell_test
  PRIVATE
    RenderWell
    Catch2::Catch2
)

#------------------------------------------------------------------------------
# Create dependencies with RenderWell_test on each of the test plugins
#------------------------------------------------------------------------------
set_target_properties(RenderWell_test
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:RenderWell>
)

target_compile_definitions(RenderWell_test
  PRIVATE
    RENDERWELL_BUILD_DIR="$<TARGET_FILE_DIR:RenderWell_test>"
    RENDERWELL_PLUGIN_COUNT=${RENDERWELL_PLUGIN_COUNT}
)

target_compile_options(RenderWell_test
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/MP>
)

target_include_directories(RenderWell_test PRIVATE ${RENDERWELL_GENERATED_DIR})

catch_discover_tests(RenderWell_test)
