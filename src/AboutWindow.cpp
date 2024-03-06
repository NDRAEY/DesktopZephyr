//
// Created by ndraey on 6.3.2024.
//

#include "../include/AboutWindow.hpp"
#include "../include/Version.hpp"
#include <string>

AboutWindow::AboutWindow() {
    progname_label.setText("<b>Desktop Zephyr</b>");

    QFont fnt = (QFont)progname_label.font();
    fnt.setPointSize(22);

    progname_label.setFont(fnt);

    description_label.setText(QString("Version: %1<br/><i>by NDRAEY</i>").arg(VERSION_STR));
    description_label.setAlignment(Qt::AlignCenter);

    layout.addWidget(&progname_label);
    layout.addWidget(&description_label);

    setLayout(&layout);
}
