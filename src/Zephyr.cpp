//
// Created by ndraey on 24.2.2024.
//

#include "../include/Zephyr.hpp"
#include <QTimer>
#include <QApplication>
#include <QMenu>
#include <QDateTime>
#include "../include/AboutWindow.hpp"

Zephyr::Zephyr(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint) {
    setAttribute(Qt::WA_TranslucentBackground);

    setMouseTracking(true);

    // Layout
    layout = new QVBoxLayout(this);

    layout->setAlignment(Qt::AlignBottom);

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

    // Context Menu
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &QWidget::customContextMenuRequested,
            this, &Zephyr::showContextMenu);

    // Mouse chasing

    connect(&cursor_chaser_timer, &QTimer::timeout, this, &Zephyr::animateChasingFrame);

    // Mouse tracking

    mouse_tracker_thread = QThread::create([&](){
        forever {
            if(this->is_freeing) {
                break;
            }

            auto mouse_tracker_coords = QCursor::pos();

            int win_x = this->x() + (this->width() / 2);

            if(mouse_tracker_coords.x() <= win_x) {
                lookLeft();
            } else {
                lookRight();
            }

            QThread::msleep(25);
        }
    });
}

Zephyr::~Zephyr() {
    is_freeing = true;
    mouse_tracker_thread->quit();
    mouse_tracker_thread->wait();
    frameswitch_timer->stop();
    disconnect(&cursor_chaser_timer);

    delete bubble;
    delete image_label;
    delete layout;
    delete mouse_tracker_thread;
}

void Zephyr::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        auto position = event->globalPosition().toPoint() - dragging_position;
        auto screen = ::QApplication::primaryScreen()->geometry();

        move({
            position.x(),
            qMin(position.y(), screen.height() - height())
        });

        event->accept();
    }
}

void Zephyr::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(QDateTime::currentMSecsSinceEpoch() - last_click_ms < 250) {
            chaseTheCursor();
        }

        last_click_ms = QDateTime::currentMSecsSinceEpoch();

        dragging_position = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
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

    auto size = current_animation->largestFrameSize();

    this->setFixedSize(size);
}

void Zephyr::startAnimation() {
    frameswitch_timer->start(1000 / ZEPH_FRAMESWITCH_RATE);
}

void Zephyr::stopAnimation() {
    frameswitch_timer->stop();
}

void Zephyr::showBubble(const QString& text, qsizetype duration) {
    auto metrics = bubble->getFontMetrics();
    auto measurement = metrics.boundingRect({0, 0, bubble->width(), 0}, Qt::TextWordWrap, text);

    bubble->setFixedHeight(measurement.height() + 20);
    bubble->setText(text);
    bubble->show();

    auto cur_size = size();
    auto after_coords = geometry();
    auto bubble_height = bubble->height();

    cur_size.setHeight(cur_size.height() + bubble_height);

    setFixedSize(cur_size);
    move({after_coords.x(), after_coords.y() - bubble_height});

    QTimer::singleShot(duration, this, [&](){
        auto coords = geometry();
        auto after_bubble_height = bubble->height();

        bubble->hide();

        auto sz = size();
        sz.setHeight(sz.height() - after_bubble_height);
        setFixedSize(sz);

        move({coords.x(), coords.y() + after_bubble_height});
    });
}

void Zephyr::showContextMenu(const QPoint &pos) {
    QMenu contextMenu(tr("Context menu"), this);

    contextMenu.addAction(tr("About"), this, [&] {
        auto* window = new AboutWindow();
        window->show();
    });

    contextMenu.addAction(tr("Exit"), this, [&]{
        QApplication::quit();
    });

    contextMenu.exec(mapToGlobal(pos));
}

void Zephyr::lookLeft() {
    if(!looking_direction) /* Is Left? */ {
        return;
    }

    for(const auto animation : animations) {
        animation->mirror(true, false);
    }

    looking_direction = false;
}

void Zephyr::lookRight() {
    if(looking_direction) /* Is Right? */ {
        return;
    }

    for(const auto animation : animations) {
        animation->mirror(true, false);
    }

    looking_direction = true;
}

void Zephyr::enableMouseTracking() const {
    mouse_tracker_thread->start();
}

void Zephyr::disableMouseTracking() const {
    mouse_tracker_thread->quit();
}

void Zephyr::chaseTheCursor() {
    showBubble("Hey!", 1000);

    QTimer::singleShot(1500, this, [&]() {
        setAnimation("run");

        cursor_chaser_timer.start(25);
    });
}

void Zephyr::animateChasingFrame() {
    auto mypos = pos();
    auto mousepos = QCursor::pos();

    mousepos.setX(mousepos.x() - (size().width() / 2));
    mousepos.setY(mousepos.y() - (size().height() / 2));

    auto increment = mousepos - mypos;
    auto distance = increment.manhattanLength();

    if(distance < 15) {
        cursor_chaser_timer.stop();
        setAnimation("idle");
        return;
    }

    // 9 is optimal speed for fun.
    auto target = mypos + increment / (distance / 9);

    move(target);
}
