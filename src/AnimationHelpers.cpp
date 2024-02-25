//
// Created by ndraey on 25.2.2024.
//

#include "../include/AnimationHelpers.hpp"
#include <QDebug>

Animation::FrameHolder::FrameHolder(const QList<QImage *> &frames) {
    this->anim_frames = frames;
}

size_t Animation::FrameHolder::getIndex() const {
    return frame_index;
}

QImage* Animation::FrameHolder::current() {
    return anim_frames[frame_index];
}

QImage* Animation::FrameHolder::next() {
    QImage* ret = anim_frames[frame_index];

    frame_index++;

    if(frame_index >= anim_frames.length()) {
        frame_index = 0;
    }

    return ret;
}

void Animation::FrameHolder::setIndex(qsizetype index) {
    frame_index = index;
}

QSize Animation::FrameHolder::largestFrameSize() {
    if(anim_frames.empty()) {
        return {};
    }

    QImage* cur = anim_frames[0];
    QSize result = cur->size();

//    foreach (QImage* frame, anim_frames) {
//         if(frame->size().width() > cur->size().width()
//         || frame->size().height() > cur->size().height()) {
//             cur = frame;
//         }
//    }

    foreach (QImage* frame, anim_frames) {
        if(frame->size().width() > cur->size().width()) {
            result.setWidth(frame->size().width());
        }

        if(frame->size().height() > cur->size().height()) {
            result.setHeight(frame->size().height());
        }
    }

    return result;
}

void Animation::FrameHolder::mirror(bool horizontally, bool vertically) {
    for(QImage* image : anim_frames) {
        image->mirror(horizontally, vertically);
    }
}

void Animation::FrameHolder::scale(double scale) {
    for(QImage* image : anim_frames) {
        int tw = (int)((double)image->width() * scale);
        int ty = (int)((double)image->height() * scale);

        // TODO: Maybe memory leak here?
        *image = image->scaled(tw, ty);
    }
}
