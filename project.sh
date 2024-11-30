# project.sh

if [[ $# -ne 1 ]]; then
    echo "Usage: ./project.sh [i | d | r]"
    exit 1
fi

option="$1"

if [[ "$option" = "d" ]]; then
    # echo "debug build"
    cmake --fresh -S . -B build -DBUILD_DBG:BOOL=1 && cmake --build build || cp ./build/compile_commands.json .
elif [[ "$option" = "r" ]]; then
    # echo "release build"
    cmake --fresh -S . -B build -DBUILD_DBG:BOOL=0 && cmake --build build || cp ./build/compile_commands.json .
else
    echo "Usage: ./project.sh [i | d | r]"
fi
