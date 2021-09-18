import shutil
import zlib
import os
import json
from typing import Dict, Any


def generate_cpp(output_dir: str = ".", config_json_filename: str = "colleen_config.json") -> None:
    os.chdir(output_dir)

    with open(config_json_filename, "r") as config_file:
        json_config = json.load(config_file)
    calculated_hash = zlib.crc32(f"{json_config}".encode("UTF-8"))

    if os.path.exists(".cpp_hash"):
        with open(".cpp_hash", "r") as hash_file:
            previous_hash = int(hash_file.read())
            if previous_hash == calculated_hash:
                print(
                    f"-- colleen config generator: hash matches - no regeneration needed"
                )
                exit(0)
            print(
                f"-- colleen config generator: hash does not match - regeneration needed"
            )

    if os.path.isdir("source"):
        shutil.rmtree("source")
    if os.path.isdir("include"):
        shutil.rmtree("include")

    os.makedirs("source/config")
    os.makedirs("include/config")

    for key in json_config:
        __generate_cpp(key, json_config[key])

    with open(".cpp_hash", "w") as hash_file:
        hash_file.write(f"{calculated_hash}")


def __generate_cpp(key: str, json_config: Dict[str, Any], base_path: str = "", ground_path: str = "config") -> None:
    assert ("." not in key)

    if "type" in json_config:
        class_name = key

        __add_class(class_name, base_path, ground_path, json_config)
    else:
        for key_ in json_config:
            for path in ["source/", "include/"]:
                complete_path = path + ground_path + "/" + base_path + "/" + key
                if not os.path.isdir(complete_path):
                    os.mkdir(complete_path)
            __generate_cpp(key_, json_config[key_], base_path + "/" + key)


def __add_class(class_name: str, base_path: str, ground_path: str, json_config: Dict[str, Any]) -> None:
    path_parts = base_path.split(sep="/")

    header_file_name = ground_path + "/".join(path_parts) + f"/{class_name}.h"
    source_file_name = ground_path + "/".join(path_parts) + f"/{class_name}.cpp"
    namespace_string = f"{ground_path}" + "::".join(path_parts)
    option_name = (".".join(path_parts) + f".{class_name}")[1:]

    option_types = {"string": "std::string", "int": "int64_t", "uint": "uint64_t", "float": "double"}
    assert json_config["type"] in option_types
    type = json_config["type"]
    option_type = option_types[type]

    required_includes = ["#include <colleen/node.h>"]
    if type == "string":
        required_includes.append("#include <string>")
    elif type in ["int", "uint"]:
        required_includes.append("#include <cstdint>")

    with open("include/" + header_file_name, "w") as include_file:
        include_file.write(f"#pragma once\n")
        for required_include in required_includes:
            include_file.write(f"{required_include}\n")
        include_file.write(f"namespace {namespace_string} {{\n")
        # add class
        include_file.write(f"using autogen_{class_name} =  colleen::node<{option_type}>;\n")
        # add instance
        include_file.write(f"extern autogen_{class_name} {class_name};")
        # end namespace
        include_file.write(f"}} // namespace {namespace_string}")

    default_value = json_config.get("default", None)
    if default_value and type == "string":
        default_value = f"\"{default_value}\""

    with open("source/" + source_file_name, "w") as source_file:
        source_file.write(f"#include \"{header_file_name}\"\n"
                          f"namespace {namespace_string} {{\n")
        if default_value:
            source_file.write(f"autogen_{class_name} {class_name}(\"{option_name}\", {default_value});\n")
        else:
            source_file.write(f"autogen_{class_name} {class_name}(\"{option_name}\");\n")
        source_file.write(f"}} // namespace {namespace_string}")
