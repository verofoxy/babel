/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** CallDialog.cpp
*/

#include <sstream>

#include "CallDialog.hpp"

Babel::CallDialog::CallDialog(QWidget *parent) : QDialog(parent), m_ui(std::make_unique<Ui_CallDialog>())
{
    m_ui->setupUi(this);
}

void Babel::CallDialog::answer()
{
    close();
}

void Babel::CallDialog::decline()
{
    close();
}

void Babel::CallDialog::setCallerName(const std::string &name)
{
    std::stringstream str;

    str << "<html><head/><body><p><span style=\" font-size:11pt;\">" << name << " is calling you..."
                                                                                "</span></p></body></html>";
    m_ui->callerNameLabel->setText(QString::fromStdString(str.str()));
}
