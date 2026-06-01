# min or newer version req of CMAKE to build
cmake_minimum_required(VERSION 3.20)


project(AllocatorSuite # project name we are building
    VERSION 1.0 # project version
    LANGUAGES CXX # this project uses C++ (CXX is CMake's name for C++).
)

set(CMAKE_CXX_STANDARD 20) # compile using C++ 20
set(CMAKE_CXX_STANDARD_REQUIRED ON) # disable auto downgrade of the C++ standard


file(GLOB_RECURSE SOURCES # find every cpp file inside src folder, "SOURCES" is the variable name in which all the files will be stored
    "src/*.cpp"
)


add_executable(AllocatorSuite ${SOURCES}) # create executable platform independent named AllocatorSuite from all the files stored inside variable "SOURCES"

target_include_directories(AllocatorSuite PRIVATE #During compilation also search inside src/private path and its subfolders
    src/public
)