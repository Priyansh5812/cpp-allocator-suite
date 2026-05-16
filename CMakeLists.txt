# CMakeList.txt : CMake project for ExpProject_Cpp, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ExpProject_Cpp "main.cpp" "main.h" "Allocator/StackAllocator.h" "Allocator/StackAllocator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ExpProject_Cpp PROPERTY CXX_STANDARD 20)
endif()

add_compile_options(/Zc:__cplusplus)

# TODO: Add tests and install targets if needed.
