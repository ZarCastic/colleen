//
// Created by Tobias Fuchs on 30.12.20.
//
#include "colleen/argument.h"

namespace Colleen::_impl_ {

ArgumentName ArgumentBase::getName() const noexcept {
    return _argument_name.has_value() ? *_argument_name : "";
}

bool ArgumentBase::isPositional() const noexcept { return _is_positional; }
bool ArgumentBase::operator==(ArgumentName argument_name) const noexcept {
    return _argument_name == argument_name;
}

}  // namespace Colleen::_impl_