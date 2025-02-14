#pragma once

#include <QObject>
#include <QDebug>

class SwitchHandler : public QObject {
    Q_OBJECT

public:
    explicit SwitchHandler(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void onSwitchToggled(bool checked) {
        if (checked) {
            qDebug() << "Переключатель включен";
        } else {
            qDebug() << "Переключатель выключен";
        }
    }
};
