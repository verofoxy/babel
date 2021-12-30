cmake_minimum_required(VERSION 3.17)
project(CPP_babel_2021  VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

if (UNIX)
    add_compile_options(-Wall -Wextra -Weffc++)
else ()
    add_compile_options(/W4)
endif()

include_directories(
        ../Common/include
        ../Common/include/Audio
        ../Common/include/Exceptions
        ../Common/include/Network
        include
        include/Widgets
        include/Network
        include/Command
)

qt_wrap_ui(QT_UI_INCLUDES
        include/Widgets/CallDialog.ui
        include/Widgets/ConnectionDialog.ui
        include/Widgets/MainWindow.ui
)

add_executable(babel_client
        ../Common/include/Audio/IAudioManager.hpp
        ../Common/src/Audio/Opus.cpp ../Common/include/Audio/Opus.hpp
        ../Common/src/Audio/PortAudio.cpp ../Common/include/Audio/PortAudio.hpp
        ../Common/src/Exceptions/AudioManagerException.cpp ../Common/include/Exceptions/AudioManagerException.hpp
        ../Common/src/Exceptions/BabelException.cpp ../Common/include/Exceptions/BabelException.hpp
        ../Common/include/Network/INetwork.hpp
        ../Common/src/Exceptions/NetworkException.cpp ../Common/include/Exceptions/NetworkException.hpp
        ${QT_UI_INCLUDES}
        src/Network/UDPNetwork.cpp include/Network/UDPNetwork.hpp
        src/Command/Command.cpp include/Command/Command.hpp
        src/Widgets/CallDialog.cpp include/Widgets/CallDialog.hpp
        src/Widgets/ConnectionDialog.cpp include/Widgets/ConnectionDialog.hpp
        src/Widgets/MainWindow.cpp include/Widgets/MainWindow.hpp
        src/Main.cpp
)

conan_target_link_libraries(babel_client
        CONAN_PKG::portaudio
        CONAN_PKG::opus
        CONAN_PKG::qt
)