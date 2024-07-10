#!/bin/bash

replacements=(
    # paths
    'cd ../../../raylib,cd ../../../prefix-raylib'
    'make PLATFORM=PLATFORM_WEB EMSDK_PATH="D:/a/raylib/raylib/emsdk-cache/emsdk-main" RAYLIB_RELEASE_PATH="../build/${{ env.RELEASE_NAME }}/lib" -B, make PLATFORM=PLATFORM_WEB EMSDK_PATH="D:/a/raylib/prefix-raylib/emsdk-cache/emsdk-main" RAYLIB_RELEASE_PATH="../build/${{ env.RELEASE_NAME }}/lib" -B'
)

for pair in "${replacements[@]}"; do
    search_for=$(echo "$pair" | cut -d',' -f1)
    replace_with=$(echo "$pair" | cut -d',' -f2)

    sed -i "s|\<$search_for\>|$replace_with|g" ./.github/workflows/*.yml
done
