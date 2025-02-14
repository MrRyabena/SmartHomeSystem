#pragma once

#include <shs_Timer.h>
#include <shs_Process.h>
#include <QTimer>
#include <QDebug>

class Ticker : public shs::Process
{
public:
    Ticker() : m_value(0) {}

    void start() override {}
    void tick() override { m_value++; }
    void stop() override {}

    unsigned getValue() { qDebug() << "tick" << m_value; return m_value; }
private:
    unsigned m_value;
};

class Timer : public QObject {
    Q_OBJECT

public:
    Timer(QObject *parent = nullptr) : QObject(parent), shs_timer(1000, &ticker) {

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Timer::checkProcess);
        timer->start(10);
    }

    Q_INVOKABLE unsigned get() { return ticker.getValue(); }

signals:
    void signal_tick();

private slots:
    void checkProcess() {
      shs_timer.tick();
      emit signal_tick();
    }


private:
    QTimer *timer;
    shs::Timer shs_timer;
    Ticker ticker;
};


