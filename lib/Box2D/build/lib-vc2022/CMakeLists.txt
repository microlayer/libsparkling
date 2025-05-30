cmake_minimum_required(VERSION 3.10)

project(Box2D)

# Setze die C++-Standardversion
set(CMAKE_CXX_FLAGS "")
set(CMAKE_C_FLAGS "")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use appropriate runtime libraries /MD for Release and /MDd for Debug
# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL" CACHE STRING "" FORCE)

# Include source files
file(GLOB SOURCES 
	"../../../Box2D/Collision/*.cpp"
	"../../../Box2D/Collision/Shapes/*.cpp" 
	"../../../Box2D/Common/*.cpp" 
	"../../../Box2D/Dynamics/*.cpp"
	"../../../Box2D/Dynamics/Contacts/*.cpp" 
	"../../../Box2D/Dynamics/Joints/*.cpp" 
	"../../../Box2D/Rope/*.cpp"
)

# Specify include directories
include_directories(
    "../../../Box2D/Collision"
	"../../../Box2D/Collision/Shapes"
    "../../../Box2D/Common"
    "../../../Box2D/Dynamics"
	"../../../Box2D/Dynamics/Contacts"
	"../../../Box2D/Dynamics/Joints"
    "../../../Box2D/Rope"
)
if(SOURCES)
    add_library(Box2D_DEBUG STATIC ${SOURCES})
	add_library(Box2D_RELEASE STATIC ${SOURCES})
else()
    message(FATAL_ERROR "No source files found to build libbox2d!")
endif()

target_include_directories(Box2D_DEBUG PUBLIC "../../../")
target_include_directories(Box2D_RELEASE PUBLIC "../../../")

if(MSVC)
	set_target_properties(Box2D_DEBUG PROPERTIES OUTPUT_NAME "libbox2dd")
	set_target_properties(Box2D_RELEASE PROPERTIES OUTPUT_NAME "libbox2d")
    target_compile_options(Box2D_DEBUG PRIVATE /W4)
	target_compile_options(Box2D_RELEASE PRIVATE /W4 /MD)
else()
    target_compile_options(Box2D_DEBUG PRIVATE -Wall)
endif()