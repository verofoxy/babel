/*
** EPITECH PROJECT, 2017
** CPP_babel_2021
** File description:
** PortAudio.hpp
*/

#pragma once

#include <mutex>
#include <queue>

#include "portaudio.h"

#include "IAudioManager.hpp"
#include "AudioManagerException.hpp"

namespace Babel {
    class PortAudio: public IAudioManager {
    public:
        PortAudio();
        PortAudio(const PortAudio &) = delete;
        ~PortAudio() override;

        PortAudio operator=(const PortAudio &) = delete;

        void startRecord() override;
        void playRecord() override;
        void stopRecord() override;
        void stopPlay() override;
        [[maybe_unused]] void dumpData(bool showData, bool showDevice) const;

        std::queue<short> getSample() override;
        [[nodiscard]] std::queue<short> &getSafeSample();
        void pushSample(std::queue<short> &sample) override;
    private:
        PaStreamParameters m_inputParameters{};
        PaStreamParameters m_outputParameters{};
        PaStream *m_inStream{};
        PaStream *m_outStream{};
        std::mutex m_lock{};
        std::queue<short> m_recordedSamples{};
        std::queue<short> m_toPlaySamples{};
        std::queue<short> m_safeRecorded{};

        void setupInputParam();
        void setupOutputParam();
        static int recordCallback(const void *inputBuffer, void *, unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *data);
        static int playCallback(const void *, void *outputBuffer, unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *data);
    };
}
