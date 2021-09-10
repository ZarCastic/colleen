#!/usr/bin/env bash

THIS_DIR=$(dirname "$0")
TEST_BUILD_DIR="${THIS_DIR}/build/colleen-tests"

while [[ $# -gt 0 ]]; do
  key="$1"
  case $key in
    --build)
      rm -rf "${TEST_BUILD_DIR}"
      "${THIS_DIR}"/build-tests.sh
      shift
      ;;
    *)
      shift
      ;;
  esac
done

"${TEST_BUILD_DIR}"/colleen-test