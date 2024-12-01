# project.sh

if [[ $# -ne 1 ]]; then
    echo "Usage: ./project.sh [i | d | r]\ni: show info, d: do debug build, r: do release build";
    exit 1
fi

if [[ "$1" = "d" ]]; then
    rm -rf ./build/ && cmake --fresh -S . -B build --preset debug-config && cmake --build build;
    cp ./build/compile_commands.json .
elif [[ "$1" = "r" ]]; then
    rm -rf ./build/ && cmake --fresh -S . -B build --preset release-config && cmake --build build;
    cp ./build/compile_commands.json .
else
    echo "Usage: ./project.sh [i | d | r]"
fi
