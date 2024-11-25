cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Host)

# Find the wxWidgets package
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Include the wxWidgets use file
include(${wxWidgets_USE_FILE})

# Add the executable
add_executable(Host WIN32 host.cpp)

# Link the wxWidgets libraries
target_link_libraries(Host ${wxWidgets_LIBRARIES})
