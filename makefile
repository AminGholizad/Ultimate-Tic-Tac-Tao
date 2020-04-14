SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >
# C++ compiler 
CXX = g++
# Compiler and linker flags (warning levels, optimisation level, 
# include debugging symbols, add include search path, add library search path)
CXXFLAGS = -Wall -Wextra -std=c++2a -O3 -I./src/inc
# Object files
OBJS := $(subst .cpp,.o,$(subst src/,obj/,$(shell ls src/*.cpp)))
# Executable name
TARGET = main.exe

$(TARGET): $(OBJS)
> $(CXX) -o $@ $(OBJS)

obj/%.o: src/%.cpp src/inc/%.hpp
> $(CXX) -o $@ -c $< $(CXXFLAGS)


obj/%.o: src/%.cpp
> $(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean
clean:
> rm -rf obj/*.o $(TARGET)