#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Argument {
 public:
  Argument(std::string arg_name, const uint64_t no_arguments,
           std::vector<std::string> options) noexcept;
  Argument(std::string arg_name, const std::string &no_arguments,
           std::vector<std::string> options) noexcept;
  Argument(const std::string &arg_name, const uint64_t no_arguments) noexcept;
  Argument(const std::string &arg_name,
           const std::string &no_arguments) noexcept;
  ~Argument() noexcept = default;

  const std::string &option(const uint64_t idx) const noexcept;
  uint64_t no_option_names() const noexcept;
  std::pair<uint64_t, bool> argumentType() const noexcept;
  const std::string &argName() const noexcept;

  virtual bool find(std::vector<std::string> argv) noexcept = 0;
  virtual const void *argument(const uint64_t idx) const noexcept = 0;

 protected:
  const uint64_t _no_arguments;
  const std::string _arg_name;
  const bool _fixed_size;
  const std::vector<std::string> _option_names;

  static uint64_t stringToArgNum(const std::string &no_arguments) noexcept;
  static std::vector<std::string> optionNameFromArgumentName(
      const std::string &no_arguments) noexcept;
};

template <typename ArgumentType>
class ArgumentImpl : public Argument {
 public:
  ArgumentImpl(const std::string &arg_name,
               const uint64_t no_arguments) noexcept;
  ArgumentImpl(const std::string &arg_name,
               const std::string &no_arguments) noexcept;
  ArgumentImpl(const std::string &arg_name, const uint64_t no_arguments,
               const std::vector<std::string> options) noexcept;
  ArgumentImpl(const std::string &arg_name, const std::string &no_arguments,
               const std::vector<std::string> options) noexcept;

  bool find(std::vector<std::string> argv) noexcept;

  ~ArgumentImpl() noexcept;

  virtual const void *argument(const uint64_t idx) const noexcept;
  const ArgumentType &operator[](const uint64_t idx) const noexcept;

  const std::vector<ArgumentType> &args() const noexcept;

 private:
  template <typename T>
  void addArgument(const std::string &arg) noexcept {
    _arguments.push_back(T(arg));
  }

  template <>
  void addArgument<int>(const std::string &arg) noexcept {
    _arguments.push_back(std::stoi(arg));
  }

  std::vector<ArgumentType> _arguments;
};

template <typename T>
ArgumentImpl<T>::ArgumentImpl(const std::string &arg_name,
                              const uint64_t no_arguments,
                              const std::vector<std::string> options) noexcept
    : Argument(arg_name, no_arguments, options) {}

template <typename T>
ArgumentImpl<T>::ArgumentImpl(const std::string &arg_name,
                              const std::string &no_arguments,
                              const std::vector<std::string> options) noexcept
    : Argument(arg_name, no_arguments, options) {}

template <typename T>
ArgumentImpl<T>::ArgumentImpl(const std::string &arg_name,
                              const uint64_t no_arguments) noexcept
    : Argument(arg_name, no_arguments) {}

template <typename T>
ArgumentImpl<T>::ArgumentImpl(const std::string &arg_name,
                              const std::string &no_arguments) noexcept
    : Argument(arg_name, no_arguments) {}

template <typename T>
ArgumentImpl<T>::~ArgumentImpl() noexcept {}

template <typename T>
bool ArgumentImpl<T>::find(std::vector<std::string> argv) noexcept {
  auto it = argv.begin();
  do {
    it = std::find_if(it, argv.end(), [this](const std::string &arg) {
      return std::find(_option_names.begin(), _option_names.end(), arg) !=
             _option_names.end();
    });
    if (it == argv.end()) {
      break;
    }

    it++;
    while ((it != argv.end()) && ((*it)[0] != '-')) {
      addArgument<T>(*it);
      it++;
    }
  } while (it != argv.end());

  return _arguments.size() >= _no_arguments;
}

template <typename T>
const void *ArgumentImpl<T>::argument(const uint64_t idx) const noexcept {
  return &(_arguments[idx]);
}

template <typename T>
const T &ArgumentImpl<T>::operator[](const uint64_t idx) const noexcept {
  return _arguments[idx];
}

template <typename T>
const std::vector<T> &ArgumentImpl<T>::args() const noexcept {
  return _arguments;
}