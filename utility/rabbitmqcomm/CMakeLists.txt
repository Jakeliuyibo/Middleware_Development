cmake_minimum_required(VERSION 3.12)
project(rabbitmqcomm)

# 搜索源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

# 搜索头文件
include_directories(
        ${HEADPATH}
        ${CMAKE_CURRENT_SOURCE_DIR}
        Y:/Codeplace_3rd-Party_Middleware/rabbitmq-install/include
    )
# 静态链接
link_directories(Y:/Codeplace_3rd-Party_Middleware/rabbitmq-install/lib)
link_libraries(Y:/Codeplace_3rd-Party_Middleware/rabbitmq-install/lib/librabbitmq.4.dll.a)
link_directories(${LIBPATH})
link_libraries(logger)

set(LIBRARY_OUTPUT_PATH ${LIBPATH})

add_library(rabbitmqcomm STATIC ${SRC})
