#!/usr/bin/env bash

THIS_DIR=$(dirname "$0")

OUTPUT_DIR="${THIS_DIR}/build/colleen-autogenerated"
CONFIGS=()

while [[ $# -gt 0 ]]; do
  key="$1"
  case $key in
    --output_dir)
      OUTPUT_DIR="$2"
      shift
      shift
      ;;
    *)
      echo "adding config $key"
      CONFIGS+=("$key")
      shift
      ;;
  esac
done

rm -rf "${THIS_DIR}"/../example/cmake-build-debug-docker-dev/colleen-autogenerated/.cpp_hash

pip3 install -r "${THIS_DIR}"/requirements.txt
python3 "${THIS_DIR}"/config_generator.py --cpp --output_dir "${OUTPUT_DIR}" "${CONFIGS[@]}"

