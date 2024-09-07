# GNU STL - libstdc++ - (libname: gnustl_static) := The official GCC STL
# STLPort - (libname: stlport_static) := A multiplatform STL; well accepted in open source projects
APP_STL      := c++_static
APP_CPPFLAGS := -fexceptions
APP_CPPFLAGS += -frtti
APP_CPPFLAGS += -std=c++17
APP_CFLAGS := -Wno-write-strings