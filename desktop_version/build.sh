#!/usr/bin/env bash
set -e

cd "$(dirname "$0")"

CC="${CC:-cc}"
if echo $'#ifdef _WIN32\nyes\n#endif' | $CC -E - | tail -n1 | grep -q yes; then
    windows=1
fi

if [ ! -d "build.$CC" ]; then
    rm -rf build
fi

mkdir -pv build.$CC/
ln -sfvn build.$CC build
cd build/

if [ -z "$dont_build" ]; then

    cmake -G Ninja \
        ${debug:+-DCMAKE_BUILD_TYPE=Debug} \
        ${debug:--DCMAKE_BUILD_TYPE=RelWithDebInfo} \
        ${windows:+-DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain.cmake -DCMAKE_MODULE_PATH="$CMAKE_MODULE_PATH"} \
        "$@" \
        ..

    ninja ${verbose:+-v}
fi

if [ ! -z "$windows" ]; then
    cp -uv ../../.github/libs/* SDL_mixer_X_build-prefix/bin/*.dll SDL_mixer_X_build-prefix/lib/*.dll . || true
fi
