//
// Created by Tobias Fuchs on 30.12.20.
//

#pragma once

#include "colleen/argument.h"
#include "colleen/common.h"

namespace Colleen::_impl_ {

// Non thread-safe argument registry singleton
class ArgumentRegistry {
   public:
    [[nodiscard]] inline uint64_t numberOfArguments() const noexcept {
        return _arguments.size();
    }
    static ArgumentRegistry& instance() {
        static ArgumentRegistry instance;
        return instance;
    }

    ~ArgumentRegistry() noexcept {
        for (auto& arg : _arguments) {
            delete arg;
        }
    }

    inline void setExecutableName(std::string executable_name) noexcept {
        _executable_name = std::move(executable_name);
    }

    [[nodiscard]] inline std::string getHelpString() const noexcept {
        std::ostringstream out_stream;
        out_stream << usageString();
        if (!_arguments.empty()) {
            out_stream << "\n\n" << positionalString();
        }
        if (!_arguments.empty()) {
            out_stream << "\n\n" << optionsString();
        }
        return out_stream.str();
    }

    template <class ArgumentType, class... Arguments>
    Argument<ArgumentType>& addArgument(Arguments... arguments) noexcept {
        auto new_argument =
            new Argument<ArgumentType>(std::forward<Arguments>(arguments)...);
        _arguments.push_back(new_argument);
        return *new_argument;
    }

    void parse(std::vector<std::string> argv) noexcept {}

    void resetArguments() noexcept {
        for (auto& arg : _arguments) {
            delete arg;
        }
        _arguments.clear();
        _executable_name.clear();
    }

   private:
    ArgumentRegistry() noexcept = default;

    [[nodiscard]] inline std::string usageString() const noexcept {
        std::ostringstream out_stream;
        out_stream << "USAGE: " << _executable_name;
        if (!_arguments.empty()) {
            for (const auto& arg : _arguments) {
                if (arg->isPositional()) {
                    out_stream << " " << arg->getName();
                }
            }
        }
        return out_stream.str();
    }

    [[nodiscard]] inline std::string optionsString() const noexcept {
        std::ostringstream out_stream;
        out_stream << "OPTIONS:\n";
        for (const auto& arg : _arguments) {
            if (arg->isPositional()) {
                continue;
            }
            arg->printAsOptional(out_stream);
            out_stream << "\n";
        }
        return out_stream.str();
    }

    [[nodiscard]] inline std::string positionalString() const noexcept {
        std::ostringstream out_stream;
        out_stream << "POSITIONAL:\n";
        for (const auto& arg : _arguments) {
            if (!arg->isPositional()) {
                continue;
            }
            arg->printAsPositional(out_stream);
            out_stream << "\n";
        }
        return out_stream.str();
    }

    std::string _executable_name;
    std::vector<ArgumentBase*> _arguments;
};

}  // namespace Colleen::_impl_