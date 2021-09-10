#pragma once

#include "colleen/argument.h"
#include "colleen/argument_registry.h"
#include "colleen/common.h"

namespace Colleen {

uint64_t numberOfArguments() noexcept;
void parse(std::vector<std::string> argv) noexcept;

void setExecutableName(std::string executable_name) noexcept;
std::string getHelpString() noexcept;

template <class ArgumentType, class... Arguments>
_impl_::Argument<ArgumentType>& addArgument(Arguments... arguments) noexcept {
    return _impl_::ArgumentRegistry::instance().addArgument<ArgumentType>(
        std::forward<Arguments>(arguments)...);
}

void resetArguments() noexcept;

}  // namespace Colleen
