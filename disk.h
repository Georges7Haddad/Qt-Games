#ifndef DISC_H
#define DISC_H

#include <QObject>
#include <QtWidgets>

class Disk : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Disk(QObject *parent = nullptr, QString diskColor = "black");
    QString diskColor;
    QString path;
    void flipDisk();

signals:

};

#endif // DISC_H
