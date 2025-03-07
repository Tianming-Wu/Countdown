#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{

#ifndef _WIN64
    qputenv("QT_QPA_PLATFORM", "xcb"); // On wayland switch to xcb to move window.
#endif

    QApplication a(argc, argv);

    QSharedMemory shared("__xzCountdown_Shared_u1");
    if(shared.attach(QSharedMemory::ReadOnly))
        return 0;
    shared.create(1);

    MainWindow w;
    w.show();

    return a.exec();
}
