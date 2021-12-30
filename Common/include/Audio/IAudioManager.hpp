/*
** EPITECH PROJECT, 2017
** CPP_babel_2021
** File description:
** AudioManager.hpp
*/

class IAudioManager {
    public:
        virtual ~IAudioManager() = default;

        virtual void startRecord() = 0;
        virtual void playRecord() = 0;
        virtual void stopRecord() = 0;
        virtual void stopPlay() = 0;

        [[nodiscard]] virtual std::queue<short> getSample() = 0;
        virtual void pushSample(std::queue<short> &sample) = 0;
};