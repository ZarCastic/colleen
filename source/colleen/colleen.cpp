#include "colleen/colleen.h"

namespace Colleen {

uint64_t numberOfArguments() noexcept {
    return _impl_::ArgumentRegistry::instance().numberOfArguments();
}

void setExecutableName(std::string executable_name) noexcept {
    _impl_::ArgumentRegistry::instance().setExecutableName(
        std::move(executable_name));
}

std::string getHelpString() noexcept {
    return _impl_::ArgumentRegistry::instance().getHelpString();
}
void resetArguments() noexcept {
    _impl_::ArgumentRegistry::instance().resetArguments();
}

void parse(std::vector<std::string> argv) noexcept {
    _impl_::ArgumentRegistry::instance().parse(std::move(argv));
}

}  // namespace Colleen