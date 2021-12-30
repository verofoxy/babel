/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** NetworkException.hpp
*/

#pragma once

#include "BabelException.hpp"

namespace Babel {
    class NetworkException : public BabelException {
    public:
        NetworkException(const std::string &component, const std::string &message);
        ~NetworkException() override = default;
    };
}