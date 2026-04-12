CXX = g++

# Paths - Adjust these if your folder names are different
RAYLIB_PATH = lib/raylib
INCLUDE_PATH = -I$(RAYLIB_PATH)/include -Ilib
LIBRARY_PATH = -L$(RAYLIB_PATH)/lib

# Compiler Flags
# -Wall: warnings, -std: modern C++
CXXFLAGS = -Wall -std=c++17 -g $(INCLUDE_PATH)

# Linker Flags 
# NOTE: Order matters! -lraylib must come before the system libs
LDFLAGS = $(LIBRARY_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread

# The build rule
launcher: launcher.cpp
	$(CXX) $< -o $@ $(CXXFLAGS) $(LDFLAGS)

clean:
	del launcher.exe