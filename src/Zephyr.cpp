//
// Created by ndraey on 24.2.2024.
//

#include "../include/Zephyr.hpp"
#include <QTimer>

Zephyr::Zephyr(QWidget *parent)
        : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::X11BypassWindowManagerHint) {
    setAttribute(Qt::WA_TranslucentBackground);

    // Layout
    layout = new QVBoxLayout(this);

    layout->setAlignment(Qt::AlignBottom);

//    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setContentsMargins(0, 0, 0, 0);

    // Bubble
    bubble = new TextBubble(this);

    bubble->setBackground(QColor{255, 255, 255});
    bubble->setBorderColor(QColor{0, 0, 0});
    bubble->hide();

    layout->addWidget(bubble);

    // Label for image
    image_label = new QLabel(this);

    // Add image to this widget
    layout->addWidget(image_label);


    // Animations
    frameswitch_timer = new QTimer(this);
    connect(frameswitch_timer, &QTimer::timeout, this, [&](){
        updatePixmap();
    });
}

Zephyr::~Zephyr() {
    delete bubble;
    delete image_label;
    delete layout;
}

void Zephyr::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - dragging_position);
        event->accept();
    }
}

void Zephyr::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        dragging_position = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void Zephyr::doSomething() {
    bubble->setFixedHeight(100);
    bubble->setFixedWidth(250);
    bubble->setText("Hello! I'm Zephyr and i'm in your computer! So this is Qt6 and after release, whole source code will be uploaded to GitHub. Zephyr tets test test. ZE-RA!!!");
    bubble->show();

    auto after_coords = geometry();
    auto bubble_height = bubble->height();
    move({after_coords.x(), after_coords.y() - bubble_height});
}

void Zephyr::doSomething2() {
    auto after_coords = geometry();
    auto bubble_height = bubble->height();

    bubble->hide();

    move({after_coords.x(), after_coords.y() + bubble_height});
}

void Zephyr::updatePixmap(bool switch_to_next) {
    QImage* image;

    if(switch_to_next) {
        image = current_animation->next();
    } else {
        image = current_animation->current();
    }

    image_label->setPixmap(QPixmap::fromImage(*image));
}

void Zephyr::setAnimation(const QString &name) {
    current_animation = animations.value(name);

    this->setFixedSize(current_animation->largestFrameSize());
}

void Zephyr::startAnimation() {
    frameswitch_timer->start(1000 / ZEPH_FRAMESWITCH_RATE);
}

void Zephyr::stopAnimation() {
    frameswitch_timer->stop();
}

void Zephyr::showBubble(const QString& text, qsizetype duration) {
    bubble->setFixedHeight(100);
    bubble->setFixedWidth(250);
    bubble->setText(text);
    bubble->show();


    auto cur_size = size();
    auto after_coords = geometry();
    auto bubble_height = bubble->height();

    cur_size.setHeight(cur_size.height() + bubble_height);

    setFixedSize(cur_size);
    move({after_coords.x(), after_coords.y() - bubble_height});

    QTimer::singleShot(duration, this, [&](){
        auto after_coords = geometry();
        auto bubble_height = bubble->height();

        bubble->hide();

        auto cur_size = size();
        cur_size.setHeight(cur_size.height() - bubble_height);
        setFixedSize(cur_size);

        move({after_coords.x(), after_coords.y() + bubble_height});
    });
}
