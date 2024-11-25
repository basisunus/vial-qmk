cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Host)

# Find the wxWidgets package
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Include the wxWidgets use file
include(${wxWidgets_USE_FILE})

file(GLOB src *.cpp)
file(GLOB hdr *.h)
SET(icon_rc "Host.rc")
SET(icns "squares.ico")
SET(manifest_file "host.manifest")
ADD_DEFINITIONS(-DICON_RC_FILE="${icns}")
SET(src ${src} ${icon_rc} ${manifest_file})

# Define where HIDAPI static libraries are located for both debug and release
set(HIDAPI_LIB_DIR_DEBUG "${CMAKE_SOURCE_DIR}/hidapi/lib/debug")
set(HIDAPI_LIB_DIR_RELEASE "${CMAKE_SOURCE_DIR}/hidapi/lib/release")
set(HIDAPI_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/hidapi/include")

# Add HIDAPI include directories
include_directories(${HIDAPI_INCLUDE_DIR})

# Add the executable
add_executable(Host WIN32 ${src} ${hdr} ${icns})

# Link the wxWidgets libraries
target_link_libraries(Host ${wxWidgets_LIBRARIES}
  $<$<CONFIG:Debug>:${HIDAPI_LIB_DIR_DEBUG}/hidapi.lib>
  $<$<CONFIG:Release>:${HIDAPI_LIB_DIR_RELEASE}/hidapi.lib>
)

# Include directories
target_include_directories(Host PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
