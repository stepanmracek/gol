cmake_minimum_required(VERSION 2.8)
project(GameOfLifeApp)

file(GLOB_RECURSE sources "*.cpp")
file(GLOB_RECURSE headers "*.h")

add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} GameOfLifeLib)
