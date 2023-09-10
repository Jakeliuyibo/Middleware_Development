project(timer)

# 搜索源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

# 搜索头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# find_package(Threads)

include_directories(${HEADPATH})
link_directories(${LIBPATH})
link_libraries(singleton)

set(LIBRARY_OUTPUT_PATH ${LIBPATH})
add_library(timer STATIC ${SRC})
