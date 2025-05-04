# Makefile to build lodepng

VERSION=1.0
PROJECTNAME:=lodepng

SRC_FILES := $(wildcard ../../*.cpp)

CC=emcc
CFLAGS=-c

# http://kripken.github.io/emscripten-site/docs/optimizing/Optimizing-Code.html
OPTIMIZERFLAGS=-O2
EXCEPTIONS=-s DISABLE_EXCEPTION_CATCHING=1

# 32MB memory for asm.js
MEMORY=-s TOTAL_MEMORY=33554432

# WASM
WASM=-s WASM=0

lodepng:$(SRC_FILES) 
	emcc -c -o $(PROJECTNAME).bc $(SRC_FILES) $(CFLAGS) $(OPTIMIZERFLAGS) $(EXCEPTIONS) -flto
	
clean:
    # TODO