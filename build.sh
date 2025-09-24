#!/usr/bin/env bash

PROJECT_DIR="$(pwd)"
BUILD_DIR="${PROJECT_DIR}/build"

check_dependency() {
    if ! command -v "$1" &> /dev/null; then
        echo "Error: $1 not installed or not found in PATH."
        exit 1
    else
        echo "[OK] $1 found."
    fi
}

echo "Checking dependencies..."
check_dependency cmake
check_dependency ninja

if command -v qmake6 &> /dev/null; then
    echo "[OK] Qt6 found (qmake6)."
elif command -v qmake-qt6 &> /dev/null; then
    echo "[OK] Qt6 found (qmake-qt6)."
else
    echo "Ошибка: Qt6 not found."
    exit 1
fi

echo "Creating build directory..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1

echo "Generating project..."
cmake .. -G Ninja -DCMAKE_PREFIX_PATH=$(qtpaths6 --install-prefix 2>/dev/null || echo "/path/to/Qt6")

echo "Building project..."
ninja

echo "Building complete. Executable - ${BUILD_DIR}/src/weather-2."

