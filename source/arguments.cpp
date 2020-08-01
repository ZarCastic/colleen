#include "arguments.h"
#include <iostream>
#include <utility>

Argument::Argument(std::string arg_name, const uint64_t no_arguments,
    std::vector<std::string>  options) noexcept
  : _no_arguments(no_arguments), _arg_name(std::move(arg_name)), _fixed_size(true),
    _option_names(std::move(options)) {
}

Argument::Argument(std::string arg_name, const std::string &no_arguments,
    std::vector<std::string>  options) noexcept
  : _no_arguments(Argument::stringToArgNum(no_arguments)), _arg_name(std::move(arg_name)),
    _fixed_size(false), _option_names(std::move(options)) {
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


const std::string &Argument::option(const uint64_t idx) const noexcept {
    return _option_names[idx];
}

uint64_t Argument::no_option_names() const noexcept {
    return _option_names.size();
}

std::pair<uint64_t, bool> Argument::argumentType() const noexcept {
    return {_no_arguments, _fixed_size};
}

const std::string &Argument::argName() const noexcept {
    return _arg_name;
}

bool Argument::find(std::vector<std::string> argv) noexcept {
    throw std::runtime_error("Argument::find should not be called");
    return false;
}

const void *Argument::argument(const uint64_t idx) const noexcept {
    throw std::runtime_error("Argument::find should not be called");
    return nullptr;
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

