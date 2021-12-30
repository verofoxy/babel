/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** BabelException.hpp
*/

#pragma once

#include <exception>
#include <string>

namespace Babel {
    class BabelException : public std::exception {
    public:
        BabelException(const std::string &component, const std::string &message);
        ~BabelException() override = default;

        [[nodiscard]] const std::string &getComponent() const noexcept;
        [[nodiscard]] const char *what() const noexcept override;
    private:
        std::string m_component;
        std::string m_message;
    };
}
