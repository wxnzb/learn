cmake_minimum_required(VERSION 3.10)  # 设置CMake的最低版本要求

project(MyApplication)  # 设置项目名称，这里使用"MyApplication"作为示例

# 设置C++标准，之前的版本太低，识别不了filesystem
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)  
set(CMAKE_CXX_STANDARD_REQUIRED True)  

# 查找MySQL客户端库
find_library(MYSQLCLIENT_LIBRARIES NAMES mysqlclient PATHS /usr/lib/x86_64-linux-gnu)

# 添加s可执行文件
add_executable(s s.cpp sq.cpp json.cpp)
# 链接MySQL客户端库
target_link_libraries(s ${MYSQLCLIENT_LIBRARIES})

# 添加c可执行文件
add_executable(c c.cpp json.cpp)
# 链接MySQL客户端库
target_link_libraries(c ${MYSQLCLIENT_LIBRARIES})

# 设置包含目录，如果需要的话
include_directories(${CMAKE_CURRENT_SOURCE_DIR})