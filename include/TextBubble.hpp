//
// Created by ndraey on 24.2.2024.
//

#pragma once

#include <QWidget>

class TextBubble : public QWidget {
public:
    explicit TextBubble(QWidget* parent = nullptr);
    ~TextBubble() = default;

    void paintEvent(QPaintEvent *) override;

    void setBackground(const QColor& color);
    void setBorderColor(const QColor& color);
    void setText(const QString &text);

private:
    QString text;
    QColor background_color;
    QColor border_color;
};