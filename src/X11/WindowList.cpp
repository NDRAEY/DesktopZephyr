//
// Created by ndraey on 26.2.2024.
//

#include <QList>
#include <QPoint>
extern "C" {
    #include <X11/Xlib.h>
}
#include "WindowList.hpp"

// TODO: Check for memory leaks
QList<std::pair<QString, QPoint>> PlatformSpecific::X11::GetWindowList() {
    QList<std::pair<QString, QPoint>> list;
    Window root;
    Window parent;
    Window* children;
    unsigned int numChildren;

    Display* display = XOpenDisplay(nullptr);

    if (!display) {
        return {};
    }

    Window rootWindow = XDefaultRootWindow(display);

    if (!XQueryTree(display, rootWindow, &root, &parent, &children, &numChildren)) {
        XCloseDisplay(display);
        return {};
    }

    for (unsigned int i = 0; i < numChildren; i++) {
        Window child = children[i];

        XWindowAttributes windowAttributes;
        XGetWindowAttributes(display, child, &windowAttributes);

        int x = windowAttributes.x;
        int y = windowAttributes.y;

        char* windowName = nullptr;
        QString name = "";
        if (XFetchName(display, child, &windowName)) {
            name = windowName;
            // Free the window name
            XFree(windowName);
        }

        list.push_back({
            name, {x, y}
        });
    }

    XFree(children);
    XCloseDisplay(display);

    return list;
}