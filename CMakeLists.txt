cmake_minimum_required (VERSION 3.9)
# 3.9 is needed for CheckIPOSupported and for doxygen_add_docs.


project(My_Tests LANGUAGES C CXX )
#for multiple compiler compatibility:
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#for development:
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# for debug builds use the debug configuration of the standard libraries:
# Unfortunately MacOS doesn't ship the debug versions of standard types,
# therefore we forego the debug macro for Apple's Clang.
if(NOT (CMAKE_CXX_COMPILER_ID MATCHES "AppleClang"))
  add_compile_definitions("$<$<CONFIG:DEBUG>:_GLIBCXX_DEBUG;_LIBCPP_DEBUG>")
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options("-stdlib=libc++")
  add_link_options("-stdlib=libc++")
  message(STATUS "Will compile with libc++.")
endif()


add_subdirectory(nlohmann_json_cmake_fetchcontent)
add_subdirectory(json-schema-validator)
add_executable(test test.cpp)
target_link_libraries(test PUBLIC nlohmann_json nlohmann_json_schema_validator)
