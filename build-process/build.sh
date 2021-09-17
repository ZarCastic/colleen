#!/usr/bin/env bash

THIS_DIR=$(realpath "$(dirname "$0")")
BUILD_DIR="${THIS_DIR}/build/colleen"
COLLEEN_ROOT_DIR="${THIS_DIR}/.."

BUILD_TYPE="Release"

while [[ $# -gt 0 ]]; do
  key="$1"
  case $key in
    --release)
      BUILD_TYPE="Release"
      shift
      ;;
    --debug)
      BUILD_TYPE="Debug"
      shift
      ;;
    *)
      shift
      ;;
  esac
done

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"  || exit 1
cmake -B "${BUILD_DIR}" -S "${COLLEEN_ROOT_DIR}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
make -C "${BUILD_DIR}"