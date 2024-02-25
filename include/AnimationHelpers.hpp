//
// Created by ndraey on 25.2.2024.
//

#pragma once

#include <QImage>

namespace Animation {
    class FrameHolder {
    public:
        explicit FrameHolder(const QList<QImage *> &frames);
        ~FrameHolder() = default;

        size_t getIndex() const;
        QImage * next();
        QImage * current();
        void setIndex(qsizetype index);
        QSize largestFrameSize();
        void mirror(bool horizontally, bool vertically);

    private:
        QList<QImage*> anim_frames;
        qsizetype frame_index = 0;
    };
}
