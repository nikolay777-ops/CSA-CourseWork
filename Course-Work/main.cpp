#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include "mainwindow.h"
#include "cpumonitor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
