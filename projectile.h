#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Projectile(QObject *parent = nullptr);
    void goUpTimer(QTimer* timer, qint16 scrollCounter);
    qint16 scrollCounter;

signals:
public slots:
    void goUp();

};

#endif // PROJECTILE_H
