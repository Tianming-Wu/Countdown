#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSharedMemory shared("__xzCountdown_Shared_u1");
    if(shared.attach(QSharedMemory::ReadOnly))
        return 0;
    shared.create(1);

    MainWindow w;
    w.show();

    return a.exec();
}
