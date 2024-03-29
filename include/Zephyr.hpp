//
// Created by ndraey on 24.2.2024.
//

#pragma once

#include <QWidget>
#include <string>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <qimage.h>
#include <QLabel>
#include <QProcess>
#include <QThread>
#include <QTimer>
#include "TextBubble.hpp"
#include "AnimationHelpers.hpp"

#define ZEPH_FRAMESWITCH_RATE 7

class Zephyr : public QWidget {
public:
    explicit Zephyr(QWidget* parent = nullptr);
    ~Zephyr() override;

    void updatePixmap(bool switch_to_next = true);

    void setAnimation(const QString& name);

    void startAnimation();
    void stopAnimation();

    void showBubble(const QString& text, qsizetype duration);
    void showContextMenu(const QPoint &pos);

    void enableMouseTracking() const;
    void disableMouseTracking() const;

    void lookLeft();
    void lookRight();

    void chaseTheCursor();

    QMap<QString, Animation::FrameHolder*> animations;
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    bool is_freeing = false;

    QVBoxLayout *layout = nullptr;

    Animation::FrameHolder* current_animation = nullptr;

    QLabel* image_label = nullptr;

    QPoint dragging_position;

    TextBubble* bubble = nullptr;

    QTimer* frameswitch_timer = nullptr;

    QThread* mouse_tracker_thread = nullptr;

    // Left = false, Right = true
    bool looking_direction = false;

    // When last click on Zephyr happened?
    qint64 last_click_ms = 0;

    QTimer cursor_chaser_timer;

    void animateChasingFrame();
};
