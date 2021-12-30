/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** MainWindow.hpp
*/

#pragma once

#include <string>
#include <unordered_map>
#include <QMainWindow>

#include "ui_MainWindow.h"

namespace Babel {
    class MainWindow : public QMainWindow {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        MainWindow(const MainWindow &) = delete;
        ~MainWindow() override = default;

        MainWindow &operator=(const MainWindow &) = delete;

        void fillContactList(const std::unordered_map<std::string, std::string> &contacts);

        void setUsername(const std::string &username);
        void setPhoneNumber(const std::string &phone);
        void setOnlineContacts(std::size_t online);
        void setServerInfos(const std::string &ip, const std::string &port);
    private:
        std::unique_ptr<Ui_MainWindow> m_ui;
        std::string m_serverIp{};
        std::string m_serverPort{};
    private slots:
        void call();
        void hangOut();
    };
}

