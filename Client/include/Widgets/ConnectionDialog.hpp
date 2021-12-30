/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** ConnectionDialog.hpp
*/

#pragma once

#include <QDialog>

#include "ui_ConnectionDialog.h"

namespace Babel {
    class ConnectionDialog : public QDialog {
        Q_OBJECT
    public:
        explicit ConnectionDialog(QWidget *parent = nullptr);
        ~ConnectionDialog() override = default;
    private:
        std::unique_ptr<Ui_ConnectionDialog> m_ui;
    private slots:
        void save();
        void cancel();
    };
}
