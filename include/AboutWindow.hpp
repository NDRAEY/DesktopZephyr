//
// Created by ndraey on 6.3.2024.
//

#pragma once

#include <QWindow>
#include <QLabel>
#include <QVBoxLayout>

class AboutWindow : public QWidget {
public:
    AboutWindow();
    ~AboutWindow() override = default;

private:
    QVBoxLayout layout;
    QLabel progname_label;
    QLabel description_label;
};