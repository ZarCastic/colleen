import argparse
import json
import os
from jsonmerge import merge
from typing import List, Final, Dict, Any

from generators.cpp_generator import generate_cpp

config_json_filename: Final[str] = "colleen_config.json"


def merge_configs(configs: List[str], output_dir: str = ".") -> None:
    print(f"-- colleen config generator: OUTPUT_DIR= {output_dir}")
    print(f"-- colleen config generator: CONFIGS= {configs}")

    if not os.path.isdir(output_dir):
        os.mkdir(output_dir)

    result: Dict[str, Any] = dict()
    for f1 in configs:
        with open(f1, "r") as infile:
            f = json.load(infile)
            result = merge(result, f)

    with open(output_dir + "/" + config_json_filename, "w") as output_file:
        json.dump(result, output_file)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Generate configuration structs for various programming languages"
    )
    parser.add_argument(
        "configs",
        metavar="CONFIG",
        type=str,
        nargs="+",
        help="Json file for configuration",
    )
    parser.add_argument(
        "--cpp",
        dest="generate_cpp",
        action="store_true",
        help="Generate C++ configuration structs",
    )
    parser.add_argument(
        "--no_cpp",
        dest="generate_cpp",
        action="store_false",
        help="Generate C++ configuration structs",
    )
    parser.add_argument(
        "--output_dir",
        dest="output_dir",
        type=str,
        default=".",
        help="Output directory for configuration structs",
    )

    args = parser.parse_args()
    merge_configs(args.configs, args.output_dir)

    if args.generate_cpp:
        generate_cpp(args.output_dir)
