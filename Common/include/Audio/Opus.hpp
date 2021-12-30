/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** Opus.hpp
*/

#pragma once

#include <queue>

#include "opus.h"

#include "AudioManagerException.hpp"

namespace Babel {
    struct EncodedData {
        unsigned char       *sample;
        int                 nbBytes;
    };

    static constexpr int O_FRAME_PER_BUFFER = 960;

    class Opus {
    public:
        Opus();
        Opus(const Opus &) = delete;
        ~Opus() = default;

        Opus operator=(const Opus &) = delete;

        void setupDecoder();
        void setupEncoder();
        void destroyEncoder() const;
        void destroyDecoder() const;

        void encode(std::queue<short> &samples);
        void decode(EncodedData &encoded);

        EncodedData &getEncodedSound();
        std::queue<short> &getDecodedSound();
    private:
        OpusEncoder *m_encoder{};
        OpusDecoder *m_decoder{};

        EncodedData m_encodedSound{};
        std::queue<short> m_decodedSound{};
    };
}
