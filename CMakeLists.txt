# 1. 指定CMake最低版本（兼容主流环境）
cmake_minimum_required(VERSION 3.10)

# 2. 设置项目名称和使用的语言（C语言）
project(netstack_log C)

# 3. 设置C语言标准（对应之前的-std=c99）
set(CMAKE_C_STANDARD 99)
# 强制使用指定的C标准，不降级
set(CMAKE_C_STANDARD_REQUIRED ON)

# 4. 设置编译选项（开启警告，方便调试）
add_compile_options(-Wall -Wextra -Werror=implicit-function-declaration)

# 5. 声明头文件目录（让编译器能找到include/netstack/log.h）
include_directories(include)

# 6. 收集所有源文件（也可以手动列出）
file(GLOB SOURCES 
    src/*.c          # 匹配src下所有.c文件
    test/*.c
)

# 7. 生成可执行文件（指定可执行文件名 + 源文件列表）
add_executable(netstack_app ${SOURCES})

# （可选）如果后续要编译成库文件（比如供其他模块调用），可以用这个配置
# add_library(netstack_log SHARED src/log.c)  # 动态库
# add_library(netstack_log STATIC src/log.c)  # 静态库
# target_include_directories(netstack_log PUBLIC include)  # 库的头文件目录