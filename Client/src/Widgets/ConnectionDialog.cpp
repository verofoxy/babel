/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** ConnectionDialog.cpp
*/

#include "ConnectionDialog.hpp"

Babel::ConnectionDialog::ConnectionDialog(QWidget *parent)
    : QDialog(parent), m_ui(std::make_unique<Ui_ConnectionDialog>())
{
    m_ui->setupUi(this);
}

void Babel::ConnectionDialog::save()
{
    close();
}

void Babel::ConnectionDialog::cancel()
{
    close();
}
