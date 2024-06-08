# 引用头文件
include_directories(${HEADPATH})

# 链接静态库和动态库
link_directories(${LIBPATH})
link_libraries(testmodule systime singleton httpserver threadpool vector logger timer jsonparser smartptr rabbitmqclient rbtree singleton_safe slotmap)

# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${EXECPATH})

# 生成可执行文件
add_executable(test_rabbitmqclient test_rabbitmqclient.cpp)
add_executable(test_rbtree test_rbtree.cpp)
add_executable(test_singleton_safe test_singleton_safe.cpp)
add_executable(test_visitor test_visitor.cpp)
add_executable(test_slotmap test_slotmap.cpp)