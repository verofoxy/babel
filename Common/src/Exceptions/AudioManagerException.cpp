/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** AudioManagerException.cpp
*/

#include "AudioManagerException.hpp"

Babel::AudioManagerException::AudioManagerException(const std::string &component, const std::string &message)
    : BabelException(component, message)
{
}
