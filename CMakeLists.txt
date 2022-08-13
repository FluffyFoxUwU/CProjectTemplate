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

##################################
## Dont touch anything but this ##
##################################
set(ExampleProject_SOURCES
  src/dummy.c
)

set(ExampleProject_TEST_SOURCES
  src/specials.c
  src/premain.c
  src/main.c
)
  
# Suppression files (abusing configure)
configure_file(
  ${PROJECT_SOURCE_DIR}/suppressions/UBSan.supp 
  ${PROJECT_BINARY_DIR}/suppressions/UBSan.supp
)

##################################
include(scripts/process_dot_config.cmake)
include(scripts/compiler_and_link_flags.cmake)

configure_file(src/config.h src/processed_config.h)
configure_file(${PROJECT_SOURCE_DIR}/.config ${PROJECT_BINARY_DIR}/.config)

add_library(ExampleProject ${ExampleProject_SOURCES})
target_include_directories(ExampleProjectCommonFlags PUBLIC "${PROJECT_SOURCE_DIR}/include")

## Deps here ##
target_link_libraries(ExampleProject ExampleProjectCommonFlags)
###############

add_executable(ExampleProjectTest ${ExampleProject_TEST_SOURCES})
target_link_libraries(ExampleProjectTest ExampleProjectCommonFlags)
target_link_libraries(ExampleProjectTest ExampleProject)











