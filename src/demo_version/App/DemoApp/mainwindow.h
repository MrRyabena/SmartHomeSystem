#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPolygonF>
#include <QGraphicsScene>
#include <QDebug>
#include <vector>
#include <algorithm>

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

    std::vector<double> ThermBuf;
    std::vector<double> PhotoBuf;

    const int maxBufSize = 200;

private slots:
void resizeEvent(QResizeEvent*);


void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;

};



#endif // MAINWINDOW_H
