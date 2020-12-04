#ifndef VIRUS_H
#define VIRUS_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Virus : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Virus(QObject *parent = nullptr, qint8 size = 70);
    qint8 size;

signals:

public slots:
};

#endif // VIRUS_H
