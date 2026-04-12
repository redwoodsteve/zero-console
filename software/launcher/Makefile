ifeq ($(OS),Windows_NT)
    # Windows Settings
    LDFLAGS = -Llib/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
    INCLUDE = -Ilib/raylib/include -Ilib
    EXE = launcher.exe
else
    # Raspberry Pi Settings
    # We assume you ran 'sudo make install' when building raylib on the Pi
    LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt
    
    # If you are using the DRM/KMS (No Desktop) mode, use these instead:
    # LDFLAGS = -lraylib -lGLESv2 -lEGL -ldrm -lgbm -lpthread -lrt -lm -ldl
    
    INCLUDE = -I/usr/local/include -Ilib
    EXE = launcher
endif

$(EXE): launcher.cpp
	$(CXX) $< -o $@ $(CXXFLAGS) $(INCLUDE) $(LDFLAGS)