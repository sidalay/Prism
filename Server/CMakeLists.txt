project(TCP_Server)

add_executable(${PROJECT_NAME}
  src/server.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32.lib)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} INTERFACE -Wextra -Wall -Wpedantic)