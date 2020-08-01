#pragma once

#include <string>
#include <vector>
#include "arguments.h"

class Colleen {
  struct ArgIterator {
    ArgIterator(const uint64_t idx,
                std::vector<Argument *> &arguments) noexcept;

    ArgIterator &operator++() noexcept;
    Argument &operator*() noexcept;
    bool operator==(const ArgIterator &rhs) const noexcept;
    bool operator!=(const ArgIterator &rhs) const noexcept;

    uint64_t getIdx() const noexcept;

   private:
    uint64_t _idx;
    std::vector<Argument *> &_arguments;
  };

 public:
  Colleen() noexcept;
  virtual ~Colleen() noexcept;

  template <typename T>
  void addArgument(std::string argument_name,
                   const uint64_t no_arguments) noexcept;

  template <typename T>
  void addArgument(std::string argument_name,
                   const std::string &no_arguments) noexcept;

  template <typename T>
  void addArgument(std::string argument_name, const uint64_t no_arguments,
                   const std::vector<std::string> &option_names) noexcept;

  template <typename T>
  void addArgument(std::string argument_name, const std::string &no_arguments,
                   const std::vector<std::string> &option_names) noexcept;

  template <typename T>
  ArgumentImpl<T> &argument(const uint64_t idx) noexcept;

  uint64_t noArgs() const noexcept;

  const Argument *operator[](const uint64_t idx) const noexcept;
  ArgIterator begin() noexcept;
  ArgIterator end() noexcept;

  void parse(int argc, char **argv);

 private:
  std::vector<Argument *> _arguments;
  void parse(const std::vector<std::string> argv);
};

template <typename T>
void Colleen::addArgument(std::string argument_name,
                          const uint64_t no_arguments) noexcept {
  auto new_argument = new ArgumentImpl<T>(argument_name, no_arguments);
  _arguments.push_back(new_argument);
}

template <typename T>
void Colleen::addArgument(std::string argument_name,
                          const std::string &no_arguments) noexcept {
  auto new_argument = new ArgumentImpl<T>(argument_name, no_arguments);
  _arguments.push_back(new_argument);
}

template <typename T>
void Colleen::addArgument(
    std::string argument_name, const uint64_t no_arguments,
    const std::vector<std::string> &option_names) noexcept {
  auto new_argument =
      new ArgumentImpl<T>(argument_name, no_arguments, option_names);
  _arguments.push_back(new_argument);
}

template <typename T>
void Colleen::addArgument(
    std::string argument_name, const std::string &no_arguments,
    const std::vector<std::string> &option_names) noexcept {
  auto new_argument =
      new ArgumentImpl<T>(argument_name, no_arguments, option_names);
  _arguments.push_back(new_argument);
}

template <typename T>
ArgumentImpl<T> &Colleen::argument(const uint64_t idx) noexcept {
  auto retval = _arguments[idx];
  return *(dynamic_cast<ArgumentImpl<T> *>(retval));
}
