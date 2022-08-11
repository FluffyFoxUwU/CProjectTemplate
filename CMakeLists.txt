cmake_minimum_required(VERSION 3.18)

project(ExampleProject VERSION 1.0.0
                 LANGUAGES C)

if (NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
  message(FATAL_ERROR "Non clang compiler unsupported")
endif()

# C standard checks
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(scripts/process_dot_config.cmake)
include(scripts/compiler_and_link_flags.cmake)

## Deps here ##
#add_subdirectory(libs/ExampleLib)
#if (DEFINED CONFIG_DEP_EXAMPLELIB_USE_SHARED)
#  target_link_libraries(ExampleProjectObjects ExampleLibShared)
#else()
#  target_link_libraries(ExampleProjectObjects ExampleLibStatic)
#endif()
###############

add_library(ExampleProjectObjects OBJECT
  src/dummy.c
)

configure_file(src/config.h src/processed_config.h)
configure_file(${PROJECT_SOURCE_DIR}/.config ${PROJECT_BINARY_DIR}/.config)

add_library(ExampleProjectShared SHARED)
target_link_libraries(ExampleProjectShared ExampleProjectObjects)
target_compile_options(ExampleProjectShared PRIVATE "-fvisibility=hidden")

add_library(ExampleProjectStatic STATIC)
target_link_libraries(ExampleProjectStatic ExampleProjectObjects)

# Test
add_executable(ExampleProjectTest
  src/specials.c
  src/premain.c
  src/main.c
)
target_link_libraries(ExampleProjectTest ExampleProjectCommonFlags)
target_link_libraries(ExampleProjectTest ExampleProjectObjects)

# Suppression files (abusing configure)
configure_file(
  ${PROJECT_SOURCE_DIR}/suppressions/UBSan.supp 
  ${PROJECT_BINARY_DIR}/suppressions/UBSan.supp
)










