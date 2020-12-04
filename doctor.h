#ifndef DOCTOR_H
#define DOCTOR_H

#include <QObject>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "projectile.h"

class Doctor : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Doctor(QObject *parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    QPushButton* launchButton;
    void goUpTimer(QTimer* timer);



signals:
public slots:
    void acitvateLaunchButton();
    void goUp();

};

#endif // DOCTOR_H
