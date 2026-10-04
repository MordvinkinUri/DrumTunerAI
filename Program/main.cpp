#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Drum Tuner AI");
    app.setApplicationVersion("3.0");

    MainWindow window;
    window.show();

    return app.exec();
}
