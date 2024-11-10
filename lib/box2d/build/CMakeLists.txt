cmake_minimum_required(VERSION 3.10)

project(Box2D)

# Setze die C++-Standardversion
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include source files
file(GLOB SOURCES 
	"../../Box2D/Collision/*.cpp" 
	"../../Box2D/Common/*.cpp" 
	"../../Box2D/Dynamics/*.cpp" 
	"../../Box2D/Rope/*.cpp"
)

# Specify include directories
include_directories(
    "../../Box2D/Collision"
    "../../Box2D/Common"
    "../../Box2D/Dynamics"
    "../../Box2D/Rope"
)
if(SOURCES)
    add_library(Box2D STATIC ${SOURCES})
else()
    message(FATAL_ERROR "No source files found to build libbox2d!")
endif()

target_include_directories(Box2D
    PUBLIC
        "../../"
)

if(MSVC)
    target_compile_options(Box2D PRIVATE /W4)
else()
    target_compile_options(Box2D PRIVATE -Wall)
endif()