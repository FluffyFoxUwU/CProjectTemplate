# Build config

set(BUILD_PROJECT_NAME "ExampleProject")

# Sources which common between exe and library
set(BUILD_SOURCES
  src/dummy.c
  src/util/util.c
  src/util/circular_buffer.c
  src/logging/logging.c
  
  deps/vec/vec.c
  deps/buffer/buffer.c
  deps/templated-hashmap/hashmap.c
  deps/list/list.c
  deps/list/list_node.c
  deps/list/list_iterator.c
)

set(BUILD_INCLUDE_DIRS
  deps/vec/ 
  deps/buffer/ 
  deps/templated-hashmap/ 
  deps/list/  
)

# Note that exe does not represent Windows' 
# exe its just short hand of executable 
#
# Note:
# Still creates executable even building library. 
# This would contain test codes if project is 
# library. The executable directly links to the 
# library objects instead through shared library
set(BUILD_EXE_SOURCES
  src/specials.c
  src/premain.c
  src/main.c
)

# Public header to be exported
set(BUILD_PUBLIC_HEADERS
  include/dummy.h
)

set(BUILD_PROTOBUF_FILES
)

set(BUILD_CFLAGS "")
set(BUILD_LDFLAGS "")

macro(AddDependencies)
  # Example
  # AddPkgConfigLib(FluffyGC FluffyGC>=1.0.0)
endmacro()

macro(PreConfigurationLoad)
  # Do pre config stuffs
endmacro()

macro(PostConfigurationLoad)
  # Do post config stuffs
  # like deciding whether to include or not include some files
  if (DEFINED COMPILE_UWUIFY_UTIL)
    list(APPEND BUILD_SOURCES src/util/uwuify.c)
  endif()
endmacro()

