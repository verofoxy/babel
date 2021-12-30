/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** CallDialog.hpp
*/

#pragma once

#include <string>
#include <QDialog>

#include "ui_CallDialog.h"

namespace Babel {
    class CallDialog : public QDialog {
        Q_OBJECT
    public:
        explicit CallDialog(QWidget *parent = nullptr);
        ~CallDialog() override = default;

        void setCallerName(const std::string &name);
    private:
        std::unique_ptr<Ui_CallDialog> m_ui;
    private slots:
        void answer();
        void decline();
    };
}
