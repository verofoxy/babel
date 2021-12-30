/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description: Main.cpp
** Main.cpp
*/

#include <iostream>
#include <QApplication>

#include "Opus.hpp"
#include "PortAudio.hpp"
#include "UDPNetwork.hpp"
#include "NetworkException.hpp"
#include "MainWindow.hpp"


int main(int ac, char **av)
{
    if (ac != 6) {
        std::cout << "Usage: " << av[0] << " ip sending_port listening_port server_ip server_port" << std::endl;
        return (84);
    }

    try {
        QApplication        app(ac, av);
        Babel::MainWindow   window;
        window.setServerInfos(av[4], av[5]);
        window.show();
        app.exec();

        Babel::UDPNetwork          udp(std::stoi(av[3]));
        Babel::PortAudio           lucio;
        Babel::Opus                compressor;
        std::vector<uint8_t>       data;

        compressor.setupEncoder();
        lucio.startRecord();
        while (true) {
            udp.receivePacket();
            lucio.getSample();
            if (lucio.getSafeSample().size() >= Babel::O_FRAME_PER_BUFFER) {
                compressor.encode(lucio.getSafeSample());
                for (size_t i = 0 ; compressor.getEncodedSound().sample[i]; i++)
                    data.emplace_back(compressor.getEncodedSound().sample[i]);
                Babel::PacketHeader header{.type = Babel::SOUND, .size = data.size()};
                try {
                    udp.sendPacket(av[1], std::stoi(av[2]), header, data);
                } catch (const Babel::NetworkException &e) {
                    std::cerr << e.getComponent() << ": " << e.what() << std::endl;
                }
            }
            data.clear();
        }
    } catch (const std::exception &e) {
        return (84);
    }
    return (0);
}