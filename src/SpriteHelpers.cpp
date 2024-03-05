//
// Created by ndraey on 25.2.2024.
//

#include <QFile>
#include "../include/SpriteHelpers.hpp"

QList<QImage*> Sprites::fromImagePaths(const QList<QString>& imagePaths) {
    QList<QImage*> images;

    foreach (const auto& path, imagePaths) {
        images.push_back(new QImage(path));
    }

    return images;
}
