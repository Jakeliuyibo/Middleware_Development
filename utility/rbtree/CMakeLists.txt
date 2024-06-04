project(rbtree)

# 搜索源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

# 搜索头文件
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${HEADPATH}
    )
# 静态链接
link_directories(${LIBPATH})
link_libraries(logger)

set(LIBRARY_OUTPUT_PATH ${LIBPATH})

add_library(rbtree STATIC ${SRC})