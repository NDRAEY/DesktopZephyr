//
// Created by ndraey on 24.2.2024.
//

#pragma once

#include <QWidget>
#include <QPainter>

class TextBubble : public QWidget {
public:
    explicit TextBubble(QWidget* parent = nullptr);
    ~TextBubble() override = default;

    void paintEvent(QPaintEvent *) override;

    void setBackground(const QColor& color);
    void setBorderColor(const QColor& color);
    void setText(const QString &text);
    QFontMetrics getFontMetrics() const;

private:
    QFont font;
    QString text;
    QColor background_color;
    QColor border_color;
};
