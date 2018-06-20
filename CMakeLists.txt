cmake_minimum_required(VERSION 2.8.12)

project(simple-ps)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(.)

find_package(Qt5Core)
find_package( OpenCV REQUIRED )
find_package(Qt5Widgets)



add_executable(${PROJECT_NAME} main.cpp mode_trans.cpp slot.cpp slot.h file_process.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core ${OpenCV_LIBS} Qt5::Widgets)
