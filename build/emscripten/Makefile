# Makefile to build libsparkling 

VERSION = 1.0

LIBSPARKLING_SRC_FILES := $(wildcard ../../testbed/bootstrap/emscripten/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../testbed/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/spark/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/device/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/device/window/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/log/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/renderer/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/renderer/common/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/renderer/shader/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/perspective/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/ui/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/app/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/drawing/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/file/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/mesh/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/scene/*.cpp)
LIBSPARKLING_SRC_FILES += $(wildcard ../../source/mlstl/*.cpp)

IDIRINCLUDE  	:= ../../include
IDIRSOURCE 	+= ../../source
IDIRLIBS 	+= ../../lib

CC=emcc
CFLAGS=-I$(IDIRINCLUDE) -I$(IDIRSOURCE) -I$(IDIRLIBS) -D__WEBGL__ -Wno-write-strings
LDFLAGS=

OGLSUPPORT=-s LEGACY_GL_EMULATION=0 -s FULL_ES2=1 -s USE_GLFW=3

OPTIMIZERFLAGS=-O2
EXCEPTIONS=-s DISABLE_EXCEPTION_CATCHING=1

# 32MB memory for asm.js
MEMORY=-s TOTAL_MEMORY=33554432

# WASM
WASM=-s WASM=0

sparkling:$(LIBSPARKLING_SRC_FILES) 
	emcc -o sparkling_emscripten.html $(LIBSPARKLING_SRC_FILES) $(CFLAGS) $(OGLSUPPORT) $(OPTIMIZERFLAGS) $(EXCEPTIONS) $(WASM) $(MEMORY) --memory-init-file 0

clean:
    # TODO