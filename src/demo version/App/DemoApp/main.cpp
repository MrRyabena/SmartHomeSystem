#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QThread>

#include <stdint.h>

#include "TCPstream.h"
#include <QApplication>

#include "../../../SHScore/SHSByteCollector.h"


int main(int argc, char *argv[])
{
   dtpSetup();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
