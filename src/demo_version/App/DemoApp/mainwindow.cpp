#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPoligons();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::setPoligons() {
    ThermBuf.reserve(maxBufSize);
    PhotoBuf.reserve(maxBufSize);

    QGraphicsScene *sceneT = new QGraphicsScene(ui->ThermPolygon);
    QGraphicsScene *sceneP = new QGraphicsScene(ui->PhotoPolygon);



    ui->ThermPolygon->setScene(sceneT);
    ui->PhotoPolygon->setScene(sceneP);

    ThermBuf.push_back(0.0);
    ThermBuf.push_back(10.0);
    ThermBuf.push_back(25.0);
    ThermBuf.push_back(30.0);
    ThermBuf.push_back(30.0);
    ThermBuf.push_back(30.0);
    ThermBuf.push_back(10.0);
    ThermBuf.push_back(0.0);

    updatePoligons();



}

void MainWindow::updatePoligons() {
    if (ThermBuf.size() > maxBufSize) {
        std::vector<double> n(maxBufSize);
        n.insert(n.end(), (ThermBuf.begin() + ThermBuf.size() - maxBufSize), ThermBuf.end());
        ThermBuf = n;
    }
    if (PhotoBuf.size() > maxBufSize) {
        std::vector<double> n(maxBufSize);
        n.insert(n.end(), (PhotoBuf.begin() + PhotoBuf.size() - maxBufSize), PhotoBuf.end());
        PhotoBuf = n;
    }

    auto maxT = std::max_element(ThermBuf.begin(), ThermBuf.end());
    auto maxP = std::max_element(PhotoBuf.begin(), PhotoBuf.end());

    auto minT = std::min_element(ThermBuf.begin(), ThermBuf.end());
    auto minP = std::min_element(PhotoBuf.begin(), PhotoBuf.end());

    ui->ThermPolygon->scene()->clear();
    ui->PhotoPolygon->scene()->clear();
    QPen pen(QColor(0xABBE40), 2);

    double xlast{};
    double ylast{};
    double y{};
    int x{};
    int range = *maxT - *minT + 10;
    for (int i = 0; i < ThermBuf.size(); i++) {

        y = ui->ThermPolygon->geometry().height() - (ui->ThermPolygon->geometry().height() / range) * ThermBuf[i];
        ui->ThermPolygon->scene()->addLine(xlast, ylast, x, y, pen);
        xlast = x;
        ylast = y;
        x += ui->ThermPolygon->geometry().width() / (ThermBuf.size());
    }

        xlast = 0;
        ylast = 0;
        range = *maxP - *minP + 10;
        y = 0;
        x = 0;
        for (int i = 0; i < PhotoBuf.size(); i++) {
            y = ui->PhotoPolygon->geometry().height() - (ui->PhotoPolygon->geometry().height() / range) * PhotoBuf[i];
            ui->PhotoPolygon->scene()->addLine(xlast, ylast, x, y, pen);
            xlast = x;
            ylast = y;
            x += ui->PhotoPolygon->geometry().width() / (PhotoBuf.size());
        }
    ui->ThermPolygon->scene()->setSceneRect(0, 0, ui->ThermPolygon->geometry().width() - 10, ui->ThermPolygon->geometry().height() - 10);
    ui->PhotoPolygon->scene()->setSceneRect(0, 0, ui->PhotoPolygon->geometry().width() - 10, ui->PhotoPolygon->geometry().height() - 10);
}


void MainWindow::resizeEvent(QResizeEvent*){
    updatePoligons();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    updatePoligons();
}

void MainWindow::on_pushButton_clicked()
{

}
