cmake_minimum_required(VERSION 3.1)
project(A-SoftwareRenderer)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file (GLOB SOURCE_FILES "src/*.h" "src/*.cpp")
file (GLOB MATH_FILES "src/math/*.h" "src/math/*.cpp")
set (MAIN  "main.cpp")

source_group("src" FILES ${SOURCE_FILES})
source_group("src\\math" FILES ${MATH_FILES})
source_group(" " FILES ${MAIN})


add_executable(A-SoftwareRenderer  ${MATH_FILES} ${SOURCE_FILES} ${MAIN})

