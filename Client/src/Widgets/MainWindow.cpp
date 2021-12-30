/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** MainWindow.cpp
*/

#include <iostream>
#include <sstream>

#include "MainWindow.hpp"
#include "UDPNetwork.hpp"

static const std::unordered_map<std::string, std::string> contact = {
        {"Thibault", "94.24.12.124"},
        {"Titouan", "12.52.21.126"}
};

Babel::MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(std::make_unique<Ui_MainWindow>())
{
    m_ui->setupUi(this);
    fillContactList(contact);
}

void Babel::MainWindow::call()
{
    Babel::UDPNetwork   udp(std::stoi(m_serverPort));
    std::stringstream   str;

    if (m_ui->contactList->currentRow() < 0)
        return;
    std::string contactName = m_ui->contactList->item(m_ui->contactList->currentRow(), 0)->text().toStdString();
    str << "<html><head/><body><p><span style=\" font-size:11pt;\">Calling " << contactName <<"..."
           "</span></p></body></html>";
    std::vector<uint8_t> data(contactName.begin(), contactName.end());
    Babel::PacketHeader header{.type = Babel::CALL, .size = data.size()};
    udp.sendPacket(m_serverIp, std::stoi(m_serverPort), header, data);
    m_ui->callInfosLabel->setText(QString::fromStdString(str.str()));
    m_ui->callButton->setDisabled(true);
}

void Babel::MainWindow::hangOut()
{
    Babel::UDPNetwork   udp(std::stoi(m_serverPort));
    std::vector<uint8_t> data;

    Babel::PacketHeader header{.type = Babel::HANGOUT, .size = data.size()};
    udp.sendPacket(m_serverIp, std::stoi(m_serverPort), header, data);
    m_ui->callInfosLabel->setText("<html><head/><body><p><span style=\""
                                "font-size:11pt; color:#484848;\">No phone call infos to display..."
                                "</span></p></body></html>");
    m_ui->callButton->setDisabled(false);
}

void Babel::MainWindow::fillContactList(const std::unordered_map<std::string, std::string> &contacts)
{
    auto it = contacts.begin();

    m_ui->contactList->setRowCount(static_cast<int>(contacts.size()));
    for (int i = 0; it != contacts.end(); it++, i++) {
        m_ui->contactList->setItem(i, 0, new QTableWidgetItem(it->first.c_str()));
        m_ui->contactList->setItem(i, 1, new QTableWidgetItem(it->second.c_str()));
    }
}

void Babel::MainWindow::setUsername(const std::string &username)
{
    std::stringstream str;

    str << "<html><head/><body><p><span style=\" font-size:11pt;\">Hello </span><span style=\""
           "font-size:11pt; font-weight:600;\">" << username << ",</span></p></body></html>";
    m_ui->usernameLabel->setText(QString::fromStdString(str.str()));
}

void Babel::MainWindow::setPhoneNumber(const std::string &phone)
{
    std::stringstream str;

    str << "<html><head/><body><p><span style=\" font-size:11pt;\">Your ip address is </span><span style=\""
           "font-size:11pt; font-weight:600;\">" << phone << "</span></p></body></html>";
    m_ui->ipAddressLabel->setText(QString::fromStdString(str.str()));
}

void Babel::MainWindow::setOnlineContacts(std::size_t online)
{
    std::stringstream str;

    str << "<html><head/><body><p><span style=\" font-size:11pt;\">There are </span><span style=\""
           "font-size:11pt; font-weight:600;\">" << online <<"</span><span style=\" font-size:11pt;\"> contacts online."
           "</span></p></body></html>";
    m_ui->contactOnlineLabel->setText(QString::fromStdString(str.str()));
}

void Babel::MainWindow::setServerInfos(const std::string &ip, const std::string &port)
{
    m_serverIp = ip;
    m_serverPort = port;
}