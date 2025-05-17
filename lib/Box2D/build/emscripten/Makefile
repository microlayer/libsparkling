# Makefile to build box2d

VERSION=1.0
PROJECTNAME:=box2d

SRC_FILES := $(wildcard ../../Collision/*.cpp)
SRC_FILES += $(wildcard ../../Collision/Shapes/*.cpp)
SRC_FILES += $(wildcard ../../Common/*.cpp)
SRC_FILES += $(wildcard ../../Dynamics/*.cpp)
SRC_FILES += $(wildcard ../../Dynamics/Contracts/*.cpp)
SRC_FILES += $(wildcard ../../Dynamics/Joints/*.cpp)
SRC_FILES += $(wildcard ../../Rope/*.cpp)

IDIRSOURCE 	= ../../
IDIRINCLUDE 	= ../../../

CC=emcc
CFLAGS=-I$(IDIRSOURCE) -I$(IDIRINCLUDE)


# http://kripken.github.io/emscripten-site/docs/optimizing/Optimizing-Code.html
OPTIMIZERFLAGS=-O2
EXCEPTIONS=-s DISABLE_EXCEPTION_CATCHING=1

# 32MB memory for asm.js
MEMORY=-s TOTAL_MEMORY=33554432

# WASM
WASM=-s WASM=0

# Directory to store .bc files
OBJ_DIR := build

# Final output combined .bc file
OUT_FILE := $(OBJ_DIR)/box2d.bc

# Ensure the directory exists
$(shell mkdir -p $(OBJ_DIR))

# Convert .cpp to .bc in OBJ_DIR
OBJ_FILES := $(foreach file, $(SRC_FILES), $(file:.cpp=.bc))

# Default target: compile and link
all: $(OUT_FILE)

# Compile each .cpp to .bc
%.bc: %.cpp
	emcc -c $< -o $@ $(CFLAGS) -emit-llvm
	
# Merge all .bc files to box2d.bc
#$(OUT_FILE): $(OBJ_FILES)
#	emcc $^ -o $@ -emit-llvm

# Merge all .bc files to box2d.bc
$(OUT_FILE): $(OBJ_FILES)
	../../../../build/llvm/llvm-link $^ -o $@

clean:
    # TODO