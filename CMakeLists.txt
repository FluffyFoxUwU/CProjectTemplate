cmake_minimum_required(VERSION 3.18)

project(ExampleProject VERSION 1.0.0
                 LANGUAGES C)

if (NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
  message(FATAL_ERROR "Non clang compiler unsupported")
endif()

# C standard checks
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(scripts/process_dot_config.cmake)

set(ENABLE_ASAN OFF)
set(ENABLE_MSAN OFF)
set(ENABLE_TSAN OFF)
set(ENABLE_XRAY OFF)

if (DEFINED CONFIG_ASAN) 
  set(ENABLE_ASAN ON)
endif()

if (DEFINED CONFIG_TSAN) 
  set(ENABLE_TSAN ON)
endif()

if (DEFINED CONFIG_MSAN) 
  set(ENABLE_MSAN ON)
endif()

if (DEFINED CONFIG_UBSAN) 
  set(ENABLE_UBSAN ON)
endif()

if (DEFINED CONFIG_LLVM_XRAY) 
  set(ENABLE_XRAY ON)
endif()

add_executable(ExampleProject src/main.c
                        )

target_compile_options(ExampleProject PRIVATE "-g")
target_compile_options(ExampleProject PRIVATE "-O0")
target_compile_options(ExampleProject PRIVATE "-fvisibility=hidden")
target_compile_options(ExampleProject PRIVATE "-Wall")
target_compile_options(ExampleProject PRIVATE "-fblocks")
target_compile_options(ExampleProject PRIVATE "-fno-sanitize-recover=all")
target_compile_options(ExampleProject PRIVATE "-fsanitize-recover=unsigned-integer-overflow")
target_compile_options(ExampleProject PRIVATE "-fno-omit-frame-pointer")
target_compile_options(ExampleProject PRIVATE "-fno-common")
target_compile_options(ExampleProject PRIVATE "-fno-optimize-sibling-calls")

target_compile_options(ExampleProject PRIVATE "-fsanitize=undefined")
#target_compile_options(ExampleProject PRIVATE "-fsanitize-address-use-after-return=always")
target_compile_options(ExampleProject PRIVATE "-fsanitize=float-divide-by-zero")
target_compile_options(ExampleProject PRIVATE "-fsanitize=implicit-conversion")
target_compile_options(ExampleProject PRIVATE "-fsanitize=unsigned-integer-overflow")

target_link_options(ExampleProject PRIVATE "-fsanitize=undefined")
target_link_options(ExampleProject PRIVATE "-static-libsan")

target_compile_definitions(ExampleProject PRIVATE "PROCESSED_BY_CMAKE")

if (ENABLE_ASAN)
  target_compile_options(ExampleProject PRIVATE "-fsanitize-address-use-after-scope")
  target_compile_options(ExampleProject PRIVATE "-fsanitize=address")
  target_link_options(ExampleProject PRIVATE "-fsanitize=address")
endif()

if (ENABLE_TSAN)
  target_compile_options(ExampleProject PRIVATE "-fsanitize=thread")
  target_link_options(ExampleProject PRIVATE "-fsanitize=thread")
endif()

if (ENABLE_XRAY)
  target_compile_options(ExampleProject PRIVATE "-fxray-instrument -fxray-instruction-threshold=1")
  target_link_options(ExampleProject PRIVATE "-fxray-instrument -fxray-instruction-threshold=1")
endif()

if (ENABLE_MSAN)
  target_compile_options(ExampleProject PRIVATE "-fsanitize-memory-track-origins")
  target_compile_options(ExampleProject PRIVATE "-fsanitize=memory")
  target_link_options(ExampleProject PRIVATE "-fsanitize=memory")
endif()

target_link_libraries(ExampleProject PRIVATE BlocksRuntime)
target_link_libraries(ExampleProject PRIVATE pthread)

target_include_directories(ExampleProject PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(ExampleProject PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(ExampleProject PRIVATE "${PROJECT_SOURCE_DIR}/src/collection")
target_include_directories(ExampleProject PRIVATE "${PROJECT_SOURCE_DIR}/libs")
target_include_directories(ExampleProject PRIVATE "${PROJECT_BINARY_DIR}/src")

configure_file(src/config.h src/processed_config.h)
# Abusing
configure_file(${PROJECT_SOURCE_DIR}/.config ${PROJECT_BINARY_DIR}/.config)

# Suppression files
add_custom_command(TARGET ExampleProject POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${PROJECT_SOURCE_DIR}/suppressions/UBSan.supp
                           ${PROJECT_BINARY_DIR}/suppressions/UBSan.supp
                           )



