# README

### Brief
An ongoing OpenGL 3.3 & GLFW 3.3 demo using modern C++ and CMake. This is slowly becoming a 2-D maze game.

### Sample Output
<img src="./readme_assets/Screenshot 2025-05-06 at 10.45.36 PM.png" width="320px">

### Setup Steps
 1. Get GLFW 3.3 on your system.
 2. Go to the GLAD online utility and download the appropriate files for OpenGL 3.3 core profile.
    - Drag `glad.c` into a new directory `src/Externals`.
    - Drag `glad.h` into `src/Includes/glad`, `glfw3` headers into `src/Includes/glfw`, and `khrplatform.h` into `src/Includes/KHR`.
 3. Precompile the GLAD code and GLFW code as `libglad.a` and `libglfw.3.3.dylib` respectively before placment in the `<project_root>/lib` directory.
 4. Run `project.sh d` for debug build to get started. The executable should be at `./build/src/glproject1`.
