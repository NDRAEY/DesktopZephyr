//
// Created by ndraey on 24.2.2024.
//

#include "../include/TextBubble.hpp"

#include <QPainter>

TextBubble::TextBubble(QWidget* parent)
: QWidget(parent) {}

void TextBubble::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.setPen([&]() {
        QPen pen;
        pen.setColor(border_color);
        pen.setWidth(5);
        return pen;
    }());
    painter.setBrush(background_color);

    painter.drawRect(0, 0, width(), height());

    if(!text.isEmpty()) {
        QFontMetrics ruler(painter.font());

        auto size = ruler.boundingRect(text);
//        auto coords = QPoint{size.width(), size.height()};
        auto limit = QRect{10, 10, width() - 20, height() - 20};

        painter.drawText(limit, Qt::TextWordWrap, text, &limit);
    }

    update();
}

void TextBubble::setBackground(const QColor& color) {
    background_color = color;
}

void TextBubble::setBorderColor(const QColor& color) {
    border_color = color;
}

void TextBubble::setText(const QString &text) {
    this->text = text;
}

