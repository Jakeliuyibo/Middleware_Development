cmake_minimum_required(VERSION 3.12)
project(Middleware_development)

set(CMAKE_CXX_STANDARD 11)

# 定义变量
# 静态库生成的路径
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
# 可执行文件的路径
set(EXECPATH ${PROJECT_SOURCE_DIR}/bin)
# 头文件的路径
set(HEADPATH
    ${PROJECT_SOURCE_DIR}//utility//testmodule
    ${PROJECT_SOURCE_DIR}//utility//systime
    ${PROJECT_SOURCE_DIR}//utility//singleton
    ${PROJECT_SOURCE_DIR}//utility//httpserver
    ${PROJECT_SOURCE_DIR}//utility//threadpool
    ${PROJECT_SOURCE_DIR}//utility//vector
    ${PROJECT_SOURCE_DIR}//utility//logger
    ${PROJECT_SOURCE_DIR}//utility//timer
    ${PROJECT_SOURCE_DIR}//utility//jsonparser
    ${PROJECT_SOURCE_DIR}//utility//smartptr
    )
    
# 可执行文件名称
set(APPNAME app)

# 添加子目录
add_subdirectory(utility)

# 生成APP
# 引用头文件
include_directories(${HEADPATH})
# 链接静态库
link_directories(${LIBPATH})
link_libraries(testmodule systime  singleton  httpserver threadpool vector logger timer jsonparser smartptr)
# 生成可执行文件
set(EXECUTABLE_OUTPUT_PATH ${EXECPATH})
add_executable(${APPNAME} main.cpp)
