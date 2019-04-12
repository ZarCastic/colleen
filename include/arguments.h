#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Argument {
public:
    Argument(const std::string &arg_name, const uint64_t no_arguments,
        const std::vector<std::string> options) noexcept;
    Argument(const std::string &arg_name, const std::string &no_arguments,
        const std::vector<std::string> options) noexcept;
    Argument(const std::string &arg_name, const uint64_t no_arguments) noexcept;
    Argument(const std::string &arg_name, const std::string &no_arguments) noexcept;
    ~Argument() noexcept;

    const std::string &             option(const uint64_t idx) const noexcept;
    uint64_t                        no_option_names() const noexcept;
    const std::pair<uint64_t, bool> argumentType() const noexcept;
    const std::string &             argName() const noexcept;

    virtual bool find(std::vector<std::string> argv) noexcept;

protected:
    const uint64_t                 _no_arguments;
    const std::string              _arg_name;
    const bool                     _fixed_size;
    const std::vector<std::string> _option_names;

    static uint64_t stringToArgNum(const std::string &no_arguments) noexcept;
    static std::vector<std::string> optionNameFromArgumentName(
        const std::string &no_arguments) noexcept;
};

template <typename ArgumentType> class ArgumentImpl : public Argument {
public:
    ArgumentImpl(const std::string &arg_name, const uint64_t no_arguments) noexcept;
    ArgumentImpl(
        const std::string &arg_name, const std::string &no_arguments) noexcept;
    ArgumentImpl(const std::string &arg_name, const uint64_t no_arguments,
        const std::vector<std::string> options) noexcept;
    ArgumentImpl(const std::string &arg_name, const std::string &no_arguments,
        const std::vector<std::string> options) noexcept;

    bool find(std::vector<std::string> argv) noexcept;

    ~ArgumentImpl() noexcept;

private:
    std::vector<ArgumentType> _arguments;
};

template <typename T>
ArgumentImpl<T>::ArgumentImpl(const std::string &arg_name,
    const uint64_t no_arguments, const std::vector<std::string> options) noexcept
  : Argument(arg_name, no_arguments, options) {
}

template <typename T>
ArgumentImpl<T>::ArgumentImpl(const std::string &arg_name,
    const std::string &no_arguments, const std::vector<std::string> options) noexcept
  : Argument(arg_name, no_arguments, options) {
}

template <typename T>
ArgumentImpl<T>::ArgumentImpl(
    const std::string &arg_name, const uint64_t no_arguments) noexcept
  : Argument(arg_name, no_arguments) {
}

template <typename T>
ArgumentImpl<T>::ArgumentImpl(
    const std::string &arg_name, const std::string &no_arguments) noexcept
  : Argument(arg_name, no_arguments) {
}

template <typename T> ArgumentImpl<T>::~ArgumentImpl() noexcept {
}

template <typename T>
bool ArgumentImpl<T>::find(std::vector<std::string> argv) noexcept {
    bool fullfilled = false;

    auto it = std::find_if(argv.begin(), argv.end(), [this](const std::string &arg) {
        return std::find(_option_names.begin(), _option_names.end(), arg)
            != _option_names.end();
    });

    fullfilled = (it != argv.end());
    // TODO finish
    std::cerr << "Not jet implemented fully: " << __FILE__ << ": " << __func__
              << std::endl;

    return fullfilled;
}