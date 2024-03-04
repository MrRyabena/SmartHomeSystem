#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPolygonF>
#include <QGraphicsScene>
#include <QDebug>
#include <vector>
#include <algorithm>
#include <QTcpSocket>
#include "../../../SHScore/SHSdtp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void begin();
    void setPoligons();
    void updatePoligons();
    QTcpSocket *socket;

    std::vector<double> ThermBuf;
    std::vector<double> PhotoBuf;

    void read_Data();
    shs::DTP *d{};

    const int maxBufSize = 200;

private slots:
void resizeEvent(QResizeEvent*);


void on_tabWidget_currentChanged(int index);

void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

};



#endif // MAINWINDOW_H
