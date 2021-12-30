/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** AudioManagerException.hpp
*/

#pragma once

#include "BabelException.hpp"

namespace Babel {
    class AudioManagerException : public BabelException {
    public:
        AudioManagerException(const std::string &component, const std::string &message);
        ~AudioManagerException() override = default;
    };
}
