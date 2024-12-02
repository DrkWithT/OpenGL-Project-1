# project.sh

if [[ $# -ne 1 ]]; then
    echo "Usage: ./project.sh [i | d | r | sloc]\ni: show info\nd: do debug build\nr: do release build\nsloc: count source code lines\n";
    exit 1
fi

if [[ "$1" = "d" ]]; then
    cmake --fresh -S . -B build --preset debug-config && cmake --build build;
    cp ./build/compile_commands.json .
elif [[ "$1" = "r" ]]; then
    cmake --fresh -S . -B build --preset release-config && cmake --build build;
    cp ./build/compile_commands.json .
elif [[ "$1" = "sloc" ]]; then
    wc -l ./src/Main.cpp ./src/**/*.cpp ./src/Includes/**/*.hpp
else
    echo "Usage: ./project.sh [i | d | r | sloc]\ni: show info\nd: do debug build\nr: do release build\nsloc: count source code lines\n";
fi
