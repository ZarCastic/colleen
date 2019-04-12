#include "arguments.h"
#include <iostream>

Argument::Argument(const std::string &arg_name, const uint64_t no_arguments,
    const std::vector<std::string> options) noexcept
  : _no_arguments(no_arguments), _arg_name(arg_name), _fixed_size(true),
    _option_names(options) {
}

Argument::Argument(const std::string &arg_name, const std::string &no_arguments,
    const std::vector<std::string> options) noexcept
  : _no_arguments(Argument::stringToArgNum(no_arguments)), _arg_name(arg_name),
    _fixed_size(false), _option_names(options) {
    std::cerr << "Not jet implemented: " << __FILE__ << ": " << __func__;
}

Argument::Argument(const std::string &arg_name, const uint64_t no_arguments) noexcept
  : _no_arguments(no_arguments), _arg_name(arg_name), _fixed_size(true),
    _option_names(Argument::optionNameFromArgumentName(arg_name)) {
}

Argument::Argument(
    const std::string &arg_name, const std::string &no_arguments) noexcept
  : _no_arguments(Argument::stringToArgNum(no_arguments)), _arg_name(arg_name),
    _fixed_size(false),
    _option_names(Argument::optionNameFromArgumentName(arg_name)) {
    std::cerr << "Not jet implemented: " << __FILE__ << ": " << __func__
              << std::endl;
}

Argument::~Argument() noexcept {
}

const std::string &Argument::option(const uint64_t idx) const noexcept {
    return _option_names[idx];
}

uint64_t Argument::no_option_names() const noexcept {
    return _option_names.size();
}

const std::pair<uint64_t, bool> Argument::argumentType() const noexcept {
    return {_no_arguments, _fixed_size};
}

const std::string &Argument::argName() const noexcept {
    return _arg_name;
}

bool Argument::find(std::vector<std::string> argv) noexcept {
    throw std::runtime_error("Argument::find should not be called");
    return false;
}

uint64_t Argument::stringToArgNum(const std::string &no_arguments) noexcept {
    std::cerr << "Not jet implemented: " << __FILE__ << ": " << __func__
              << std::endl;
    return 0;
}

std::vector<std::string> Argument::optionNameFromArgumentName(
    const std::string &no_arguments) noexcept {

    std::vector<std::string> option_names;
    std::string              lower_argument_name = "--";
    for(auto &x : no_arguments) {
        lower_argument_name.push_back(x);
    }

    option_names.push_back(lower_argument_name);
    return option_names;
}