//
// Created by Tobias Fuchs on 12.09.21.
//
#include <colleen/_impl/base_node.h>

namespace colleen::_impl {

base_node::base_node(std::string option_name) : _option_name(option_name) {
    registry::instance().add(std::move(option_name), this);
}
bool base_node::satisfied() { return _satisfied; }

}  // namespace colleen::_impl