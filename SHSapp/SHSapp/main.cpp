#include "mainwindow.h"

#include <QApplication>
#include <QDateTime>

#include <stdint.h>

#include "tcpclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
