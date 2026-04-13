CXX = g++
TARGET = launcher

# Paths
LIB_DIR = lib/raylib/lib
# Added -Ilib so it can find "json.hpp" inside the lib folder
INCLUDE = -Ilib/raylib/include -Ilib

# Base Flags
CXXFLAGS = -Wall -std=c++17 -g

# OS Detection and Specific Config
ifeq ($(OS),Windows_NT)
    # --- WINDOWS (MinGW) ---
    LDFLAGS = -L$(LIB_DIR)/windows -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
    EXE = $(TARGET).exe
    CLEAN_CMD = del $(EXE)
else
    # --- LINUX (Raspberry Pi) ---
    # Note: We still need the system X11/GL dev libs installed via apt
    LDFLAGS = -L$(LIB_DIR)/linux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lXrandr -lXinerama -lXi -lXcursor
    EXE = $(TARGET)
    CLEAN_CMD = rm -f $(EXE)
endif

# Default Rule
all: $(EXE)

# Build Rule
$(EXE): launcher.cpp
	$(CXX) $< -o $@ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS)

# Helper for rebuilding
rebuild: clean all

clean:
	$(CLEAN_CMD)