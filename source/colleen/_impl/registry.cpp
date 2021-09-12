//
// Created by Tobias Fuchs on 12.09.21.
//
#include <colleen/_impl/base_node.h>
#include <colleen/_impl/registry.h>
#include <iostream>
#include <sstream>
#include <vector>

namespace colleen::_impl {

registry &registry::instance() noexcept {
    static registry instance;
    return instance;
}
void registry::add(std::string option_name, base_node *node) {
    if (_options.contains(option_name)) {
        throw bad_option("Cannot add duplicate option " + option_name);
    }
    _options[option_name] = node;
}

std::vector<std::string> split(const std::string &value, char sep) {
    std::vector<std::string> retval;
    std::istringstream stream(value);
    std::string string;
    while (getline(stream, string, sep)) {
        retval.push_back(string);
    }
    return retval;
}

bool registry::parse(int argc, char **argv, parse_options options) {
    std::ostringstream error_stream;

    argv++;
    argc--;
    while (argc-- > 0) {
        const std::string argument = (*argv++);
        const auto argument_parts = split(argument, '=');
        if (argument_parts.size() != 2) {
            error_stream << "Unrecognized argument: " << argument << "\n";
            continue;
        }

        const std::string option = argument_parts[0].substr(2);  // strip "--"
        const std::string &option_value = argument_parts[1];
        if (!_options.contains(option)) {
            error_stream << "Cannot find option " << option << "\n";
        } else {
            if (!_options[option]->set(option_value)) {
                error_stream << "Cannot set option " << option << " with value "
                             << option_value << "\n";
            }
        }
    }

    for (const auto &option : _options) {
        if (!option.second->satisfied()) {
            error_stream << "Option not set " << option.first << "\n";
        }
    }

    if (!error_stream) {
        if (options == parse_options::throw_on_error) {
            throw(incomplete_or_missing_argument(error_stream.str()));
        }
        std::cerr << error_stream.str() << std::endl;
        return false;
    }
    return true;
}

}  // namespace colleen::_impl
