 /*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** PortAudio.cpp
*/

#include <iostream>

#include "PortAudio.hpp"

static constexpr int PA_SAMPLE_RATE = 48000;
static constexpr int PA_FRAME_PER_BUFFER = 960;

Babel::PortAudio::PortAudio()
{
    int err;

    err = Pa_Initialize();
    if (err != paNoError)
        throw AudioManagerException("Audio", Pa_GetErrorText(err));
}

Babel::PortAudio::~PortAudio()
{
    Pa_Terminate();
}

void Babel::PortAudio::setupInputParam()
{
    m_inputParameters.device = Pa_GetDefaultInputDevice();
    if (m_inputParameters.device == paNoDevice)
        throw AudioManagerException("Audio", "No device for output");
    m_inputParameters.channelCount = 1;
    m_inputParameters.sampleFormat = paInt16;
    m_inputParameters.suggestedLatency = Pa_GetDeviceInfo(m_inputParameters.device)->defaultLowInputLatency;
    m_inputParameters.hostApiSpecificStreamInfo = nullptr;
}

void Babel::PortAudio::setupOutputParam()
{
    m_outputParameters.device = Pa_GetDefaultOutputDevice();
    if (m_inputParameters.device == paNoDevice)
        throw AudioManagerException("Audio", "No device for input");
    m_outputParameters.channelCount = 1;
    m_outputParameters.sampleFormat = paInt16;
    m_outputParameters.suggestedLatency = Pa_GetDeviceInfo(m_outputParameters.device)->defaultLowOutputLatency;
    m_outputParameters.hostApiSpecificStreamInfo = nullptr;
}

void Babel::PortAudio::startRecord()
{
    int err;

    setupInputParam();
    err = Pa_OpenStream(&m_inStream, &m_inputParameters, nullptr, PA_SAMPLE_RATE, PA_FRAME_PER_BUFFER, paClipOff,
                          PortAudio::recordCallback, this);
    if (err != paNoError)
        throw AudioManagerException("Audio", Pa_GetErrorText(err));
    err = Pa_StartStream(m_inStream);
    if (err != paNoError)
        throw AudioManagerException("Audio", Pa_GetErrorText(err));
}

void Babel::PortAudio::playRecord()
{
    int err;

    setupOutputParam();
    err = Pa_OpenStream(&m_outStream, nullptr, &m_outputParameters, PA_SAMPLE_RATE, PA_FRAME_PER_BUFFER, paClipOff,
                          PortAudio::playCallback, this);
    if (err != paNoError)
        throw AudioManagerException("Audio", Pa_GetErrorText(err));
    err = Pa_StartStream(m_outStream);
    if (err != paNoError)
        throw AudioManagerException("Audio", Pa_GetErrorText(err));
}

void Babel::PortAudio::stopRecord()
{
    int err;

    err = Pa_StopStream(m_inStream);
    if (err != paNoError)
        throw AudioManagerException("Audio", Pa_GetErrorText(err));
}

void Babel::PortAudio::stopPlay()
{
    int err;

    err = Pa_StopStream(m_outStream);
    if (err != paNoError)
        throw AudioManagerException("Audio", Pa_GetErrorText(err));
}

int Babel::PortAudio::recordCallback(const void *inputBuffer, void *, unsigned long framesPerBuffer,
                                     const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *data)
{
    auto *userData = static_cast<PortAudio*>(data);
    const auto *rinput = static_cast<const short *>(inputBuffer);

    userData->m_lock.lock();
    for (unsigned long i = 0; i < framesPerBuffer; i++)
        userData->m_recordedSamples.emplace(rinput[i]);
    userData->m_lock.unlock();
    return (0);
}

int Babel::PortAudio::playCallback(const void *, void *outputBuffer, unsigned long framesPerBuffer,
                                   const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *data)
{
    auto *userData = static_cast<PortAudio*>(data);
    auto *woutput = static_cast<short *>(outputBuffer);

    userData->m_lock.lock();
    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        if (!userData->m_toPlaySamples.empty()) {
            woutput[i] = userData->m_toPlaySamples.front();
            userData->m_toPlaySamples.pop();
        } else
            woutput[i] = 0;
    }
    userData->m_lock.unlock();
    return (0);
}

std::queue<short> Babel::PortAudio::getSample()
{
    m_lock.lock();
    if (m_recordedSamples.size() < PA_FRAME_PER_BUFFER) {
        m_lock.unlock();
        return (m_safeRecorded); // can be null
    }
    for (int i = 0 ; i < PA_FRAME_PER_BUFFER; i++) {
        if (!m_recordedSamples.empty()) {
            m_safeRecorded.push(m_recordedSamples.front());
            m_recordedSamples.pop();
        }
    }
    m_lock.unlock();
    return (m_safeRecorded);
}

void Babel::PortAudio::pushSample(std::queue<short> &sample)
{
    m_lock.lock();
    int size = static_cast<int>(sample.size());

    for (int i = 0 ; i < size; i++) {
        m_toPlaySamples.push(sample.front());
        sample.pop();
    }
    m_lock.unlock();
}

[[maybe_unused]] void Babel::PortAudio::dumpData(bool showData, bool showDevice) const
{
    int     numDevices = Pa_GetDeviceCount();
    const   PaDeviceInfo *deviceInfo;

    if (showData) {
        std::cout << "-Recorded samples:\t" << m_recordedSamples.size() << std::endl;
        std::cout << "-To Play samples:\t" << m_toPlaySamples.size() << std::endl;
    }

    if (showDevice) {
        std::cout << "---[Devices List][" << numDevices << "]---" << std::endl;
        for(int i = 0; i < numDevices; i++) {
            deviceInfo = Pa_GetDeviceInfo(i);
            if (Pa_GetDefaultInputDevice() == i || Pa_GetDefaultOutputDevice() == i)
                std::cout << "-[used]->";
            std::cout << deviceInfo->name << ": Input: " << deviceInfo->maxInputChannels << " Output: " <<
            deviceInfo->maxOutputChannels << " Sample Rate: " << deviceInfo->defaultSampleRate << std::endl;
        }
        std::cout << "---[End Devices List]---" << std::endl;
    }
}

std::queue<short> &Babel::PortAudio::getSafeSample()
{
    return m_safeRecorded;
}
