#include "virus.h"
#include <QDir>
#include <QTimer>
#include <QGraphicsScene>


Virus::Virus(QObject *parent, qint8 size) : QObject(parent)
{
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    setPixmap((QPixmap(path + "/qtproject/pictures/killcovid/virus.png")).scaled(size, size));
    this->size = size;
}
