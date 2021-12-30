cmake_minimum_required(VERSION 3.17)
project(CPP_babel_2021  VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

if (UNIX)
    add_compile_options(-Wall -Wextra -Weffc++)
else ()
    add_compile_options(/W4)
    add_compile_definitions(_WIN32_WINNT=0x0601)
endif()

include_directories(
        ../Common/include
        ../Common/include/Audio
        ../Common/include/Exceptions
        ../Common/include/Network
        include
        include/Command
        include/Network
)

add_executable(babel_server
        ../Common/include/Audio/IAudioManager.hpp
        ../Common/src/Audio/Opus.cpp ../Common/include/Audio/Opus.hpp
        ../Common/src/Audio/PortAudio.cpp ../Common/include/Audio/PortAudio.hpp
        ../Common/src/Exceptions/AudioManagerException.cpp ../Common/include/Exceptions/AudioManagerException.hpp
        ../Common/src/Exceptions/NetworkException.cpp ../Common/include/Exceptions/NetworkException.hpp
        ../Common/src/Exceptions/BabelException.cpp ../Common/include/Exceptions/BabelException.hpp
        ../Common/include/Network/INetwork.hpp
        src/Command/Command.cpp include/Command/Command.hpp
        src/Network/UDPNetwork.cpp include/Network/UDPNetwork.hpp
        src/Server.cpp include/Server.hpp
        src/Main.cpp
)

conan_target_link_libraries(babel_server
        CONAN_PKG::portaudio
        CONAN_PKG::opus
        CONAN_PKG::asio
)