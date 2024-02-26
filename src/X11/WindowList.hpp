//
// Created by ndraey on 26.2.2024.
//

#pragma once

#include <QList>

namespace PlatformSpecific::X11 {
    QList<std::pair<QString, QPoint>> GetWindowList();
}