cmake_minimum_required(VERSION 2.8.11)

project(MemoryQt)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# set Qt path on windows
if (WIN32)
    set (CMAKE_PREFIX_PATH "C:\\Qt\\5.11.0\\mingw53_32\\")
endif(WIN32)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

message("Qt Version is " ${Qt5Widgets_VERSION})

set(memoryqt_SRC
        src/main.cpp
        src/memory.cpp
        src/Card.cpp
        src/Card.h src/FlowLayout.cpp src/FlowLayout.h)

# Tell CMake to create the helloworld executable
add_executable(MemoryQt ${memoryqt_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(MemoryQt Qt5::Widgets)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif (CMAKE_COMPILER_IS_GNUCXX)