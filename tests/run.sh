#!/bin/sh
# Compile the actual display library against a controllable I2C/OLED substitute.
set -eu
TEST_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
TEST_BUILD=$(mktemp -d)
trap 'rm -rf "$TEST_BUILD"' EXIT HUP INT TERM
c++ -std=c++17 -Wall -Wextra -I"$TEST_DIR/host" -I"$TEST_DIR/../src" \
 "$TEST_DIR/errors.cpp" "$TEST_DIR/../src/MDS_Display.cpp" -o "$TEST_BUILD/errors"
"$TEST_BUILD/errors"
