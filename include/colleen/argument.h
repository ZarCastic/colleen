//
// Created by Tobias Fuchs on 30.12.20.
//

#pragma once
#include <utility>

#include "colleen/common.h"

namespace Colleen::_impl_ {

class ArgumentBase {
   public:
    ArgumentBase(ArgumentName argument_name, bool is_optional = false,
                 bool is_positional = true) noexcept
        : _argument_name{std::move(argument_name)}
        , _is_optional{is_optional}
        , _is_positional{is_positional} {}

    explicit ArgumentBase(
        ::Colleen::Colleen::_impl_::ArgumentOption argument_option,
        bool is_optional = true, bool is_positional = false) noexcept
        : _argument_option{std::move(argument_option)}
        , _is_optional{is_optional}
        , _is_positional{is_positional} {}

    virtual ~ArgumentBase() noexcept = default;

    [[nodiscard]] ArgumentName getName() const noexcept;
    [[nodiscard]] bool isPositional() const noexcept;

    virtual ArgumentBase& setDescription(std::string description) noexcept = 0;
    virtual ArgumentBase& setOptional(bool is_optional = true) noexcept = 0;
    virtual ArgumentBase& setPositional(bool is_positional = true) noexcept = 0;

    virtual ArgumentBase& printAsOptional(
        std::ostream& out_stream) noexcept = 0;
    virtual ArgumentBase& printAsPositional(
        std::ostream& out_stream) noexcept = 0;

    bool operator==(ArgumentName argument_name) const noexcept;

   protected:
    std::optional<::Colleen::Colleen::_impl_::ArgumentOption> _argument_option;
    std::optional<ArgumentName> _argument_name;
    std::optional<std::string> _description;
    bool _is_optional;
    bool _is_positional;
};

template <class ArgumentValueType>
class Argument : public ArgumentBase {
   public:
    explicit Argument(ArgumentName argument_name, bool is_optional = false,
                      bool is_positional = true) noexcept
        : ArgumentBase(std::move(argument_name), is_optional, is_positional) {}
    explicit Argument(
        ::Colleen::Colleen::_impl_::ArgumentOption argument_option,
        bool is_optional = true, bool is_positional = false) noexcept
        : ArgumentBase(std::move(argument_option), is_optional, is_positional) {
    }

    Argument<ArgumentValueType>& setDescription(
        std::string description) noexcept override {
        _description = std::string(description);
        return *this;
    }

    Argument<ArgumentValueType>& setDefault(ArgumentValueType value) noexcept {
        _default_value = std::move(value);
        return *this;
    }

    Argument<ArgumentValueType>& setOptional(
        bool is_optional = true) noexcept override {
        _is_optional = is_optional;
        return *this;
    }

    Argument<ArgumentValueType>& setPositional(
        bool is_positional = true) noexcept override {
        _is_positional = is_positional;
        return *this;
    }

    Argument<ArgumentValueType>& printAsOptional(
        std::ostream& out_stream) noexcept override {
        constexpr auto CL_OPTION_OFFSET = "  ";
        constexpr auto CL_OPTION_LINE_LENGTH = 20;

        auto line_length = 0ul;
        if (_argument_option.has_value()) {
            out_stream << CL_OPTION_OFFSET << _argument_option.value();
            line_length = _argument_option->stringSize();
        }

        if (!_argument_name.has_value()) {
            std::ostringstream argument_name_string;
            argument_name_string << " (" << _argument_name.value() << ")";
            out_stream << argument_name_string.str();
            line_length += argument_name_string.str().size();
        }

        if (!_description.has_value()) {
            if (CL_OPTION_LINE_LENGTH > line_length) {
                out_stream << std::string(CL_OPTION_LINE_LENGTH - line_length,
                                          ' ');
            } else {
                out_stream << "\n"
                           << CL_OPTION_OFFSET
                           << std::string(CL_OPTION_LINE_LENGTH, ' ');
            }
            out_stream << _description.value();
            line_length = CL_OPTION_LINE_LENGTH + _description->size();
        }
        if (_default_value.has_value()) {
            constexpr auto default_value_offset = 2 * CL_OPTION_LINE_LENGTH;
            if (default_value_offset > line_length) {
                out_stream << std::string(default_value_offset - line_length,
                                          ' ');
            } else {
                out_stream << "\n"
                           << CL_OPTION_OFFSET
                           << std::string(default_value_offset, ' ');
            }
            out_stream << "[default: " << _default_value.value() << "]";
        }
        return *this;
    }

    Argument<ArgumentValueType>& printAsPositional(
        std::ostream& out_stream) noexcept override {
        return *this;
    }

   private:
    std::optional<ArgumentValueType> _value;
    std::optional<ArgumentValueType> _default_value;
};

}  // namespace Colleen::_impl_