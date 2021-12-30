/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** Opus.cpp
*/

#include "Opus.hpp"

static constexpr int O_CHANNELS = 1;
static constexpr int O_SAMPLE_RATE = 48000;
static constexpr int O_BITRATE = 64000;

static constexpr int O_MAX_FRAME_SIZE= 6 * Babel::O_FRAME_PER_BUFFER;
static constexpr int O_MAX_PACKET_SIZE = 3 * 1276;

Babel::Opus::Opus() : m_encodedSound({.sample = nullptr, .nbBytes = 0})
{
}

void Babel::Opus::encode(std::queue<short> &samples)
{
    int bytes;
    opus_int16 in[O_FRAME_PER_BUFFER * O_CHANNELS];
    unsigned char cbits[O_MAX_PACKET_SIZE];

    if (samples.size() >= O_FRAME_PER_BUFFER) {
        for (int i = 0; i < O_CHANNELS * O_FRAME_PER_BUFFER; i++) {
            in[i] = samples.front();
            samples.pop();
        }
        bytes = opus_encode(m_encoder, in, O_FRAME_PER_BUFFER, cbits, O_MAX_PACKET_SIZE);
        if (bytes < 0)
            throw AudioManagerException("AudioManager", opus_strerror(bytes));
        m_encodedSound = {.sample = cbits, .nbBytes = bytes};
    }
}

void Babel::Opus::decode(EncodedData &sample)
{
    opus_int16 out[O_FRAME_PER_BUFFER * O_CHANNELS];
    int frame_size;

    frame_size = opus_decode(m_decoder, sample.sample, sample.nbBytes, out, O_MAX_FRAME_SIZE, 0);
    if (frame_size < 0)
        throw AudioManagerException("AudioManager", opus_strerror(frame_size));
    for (int i = 0 ; i < frame_size ; i++)
        m_decodedSound.emplace(out[i]);
}

void Babel::Opus::setupEncoder()
{
    int err;

    m_encoder = opus_encoder_create(O_SAMPLE_RATE, O_CHANNELS, OPUS_APPLICATION_VOIP, &err);
    if (err < 0)
        throw AudioManagerException("AudioManager", opus_strerror(err));
    err = opus_encoder_ctl(m_encoder, OPUS_SET_BITRATE(O_BITRATE));
    if (err < 0)
        throw AudioManagerException("AudioManager", opus_strerror(err));
}

void Babel::Opus::setupDecoder()
{
    int err;

    m_decoder = opus_decoder_create(O_SAMPLE_RATE, O_CHANNELS, &err);
    if (err < 0)
        throw AudioManagerException("AudioManager", opus_strerror(err));
}

Babel::EncodedData &Babel::Opus::getEncodedSound()
{
    return (m_encodedSound);
}

std::queue<short> &Babel::Opus::getDecodedSound()
{
    return (m_decodedSound);
}

void Babel::Opus::destroyEncoder() const
{
    if (m_encoder)
        opus_encoder_destroy(m_encoder);
}

void Babel::Opus::destroyDecoder() const
{
    if (m_decoder)
        opus_decoder_destroy(m_decoder);
}