#include "colleen.h"
#include <iostream>
#include <stdexcept>

Colleen::Colleen() noexcept {
}

Colleen::~Colleen() noexcept {
    for(auto &x : _arguments) {
        delete x;
    }
}

const Argument *Colleen::operator[](const uint64_t idx) const noexcept {
    std::cerr << __FILE__ << ": " << __func__ << "\n\tReturning " << _arguments[idx]
              << std::endl;
    return _arguments[idx];
}

uint64_t Colleen::noArgs() const noexcept {
    return _arguments.size();
}

Colleen::ArgIterator Colleen::begin() noexcept {
    return ArgIterator(0, _arguments);
}

Colleen::ArgIterator Colleen::end() noexcept {
    return ArgIterator(_arguments.size(), _arguments);
}

void Colleen::parse(int argc, char **argv) {
    std::vector<std::string> args;
    for(int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    parse(args);
}

void Colleen::parse(std::vector<std::string> argv) {
    for(auto &arg : _arguments) {
        if(!arg->find(argv)) {
            throw std::invalid_argument("Argument not fullfilled");
        }
    }
}

/**** ARG ITERATOR *****/
Colleen::ArgIterator::ArgIterator(
    const uint64_t idx, std::vector<Argument *> &arguments) noexcept
  : _idx(idx), _arguments(arguments) {
}
Colleen::ArgIterator &Colleen::ArgIterator::operator++() noexcept {
    ++_idx;
    return *this;
}
Argument &Colleen::ArgIterator::operator*() noexcept {
    return *_arguments[_idx];
}

bool Colleen::ArgIterator::operator==(const ArgIterator &rhs) const noexcept {
    return _idx == rhs.getIdx();
}

bool Colleen::ArgIterator::operator!=(const ArgIterator &rhs) const noexcept {
    return _idx != rhs.getIdx();
}

uint64_t Colleen::ArgIterator::getIdx() const noexcept {
    return _idx;
}