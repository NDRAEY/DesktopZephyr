//
// Created by ndraey on 25.2.2024.
//

#pragma once

#include <QImage>
#include <QList>

namespace Sprites {
    QList<QImage*> fromImagePaths(const QList<QString>& imagePaths);
}
