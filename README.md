# README

### Brief
An ongoing OpenGL 3.3 & GLFW 3.3 demo using modern C++ and CMake. This may become something more interesting.

### Setup Steps
 1. Get GLFW 3.3 on your system.
 2. Go to the GLAD online utility and download the appropriate files for OpenGL 3.3 core profile.
    - Drag `glad.c` into a new directory `src/Externals`.
    - Drag `glad.h` into `src/Includes/glad`, `glfw3` headers into `src/Includes/glfw`, and `khrplatform.h` into `src/Includes/KHR`.
 3. Precompile the GLAD code and GLFW code as `libglad.a` and `libglfw.3.3.dylib` respectively before placment in the `<project_root>/lib` directory.
 4. Run `project.sh d` for debug build to get started. The executable should be at `./build/src/glproject1`.

### To-Do's
 4. Refactor Window class to debounce key input, specifically by the bottom note... Must use
