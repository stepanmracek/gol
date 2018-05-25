cmake_minimum_required(VERSION 2.8)
project(GameOfLifeApp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE sources "*.cpp")
file(GLOB_RECURSE headers "*.h")

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Qml)
find_package(Qt5Quick)

add_executable(${PROJECT_NAME} ${sources} ${headers} resources.qrc)
target_link_libraries(${PROJECT_NAME} GameOfLifeLib Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)
