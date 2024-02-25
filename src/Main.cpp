#include <QApplication>
#include <QTimer>
#include "../include/Zephyr.hpp"
#include "../include/SpriteHelpers.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QList<QImage*> running = Sprites::fromImagePaths({
        "../res/running_1.png",
        "../res/running_2.png",
        "../res/running_3.png",
        "../res/running_4.png",
        "../res/running_5.png",
        "../res/running_4.png",
        "../res/running_3.png",
        "../res/running_2.png"
    });

    Animation::FrameHolder run_holder = Animation::FrameHolder(running);
    run_holder.mirror(true, false);
    run_holder.scale(0.5);


    QList<QImage*> idle = Sprites::fromImagePaths({
          "../res/idle_1.png",
          "../res/idle_2.png",
          "../res/idle_3.png",
          "../res/idle_4.png",
          "../res/idle_5.png",
          "../res/idle_6.png",
    });

    Animation::FrameHolder idle_holder = Animation::FrameHolder(idle);
    idle_holder.mirror(true, false);
    idle_holder.scale(0.5);


    Zephyr test;
    test.animations["run"] = &run_holder;
    test.animations["idle"] = &idle_holder;
    test.setAnimation("run");
    test.updatePixmap(false);
    test.show();

    test.startAnimation();

    test.move({-200, app.primaryScreen()->geometry().height() - test.height()});

    QTimer introtimer(&test);
    test.connect(&introtimer, &QTimer::timeout, &test, [&]() {
        auto pos = test.pos();
        pos.setX(pos.x() + 10);

        test.move(pos);
    });
    introtimer.start(50);

    QTimer::singleShot(5000, &test, [&]() {
        introtimer.stop();

        test.stopAnimation();

        test.setAnimation("idle");
        test.updatePixmap();

        auto pos = test.pos();
        pos.setY(app.primaryScreen()->geometry().height() - test.height());

        test.move(pos);

        test.startAnimation();

        test.showBubble("ZE... RA? ZERA-ORA!", 3000);
    });

    return app.exec();
}
