#include "projectile.h"
#include <random>
#include <QDir>

Projectile::Projectile(QObject *parent) : QObject(parent)
{
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    int i = rand() % 2;
    if(i ==0)
        setPixmap((QPixmap(path + "/qtproject/pictures/killcovid/pill.png")).scaled(30,30));
    else
        setPixmap((QPixmap(path + "/qtproject/pictures/killcovid/mask.png")).scaled(30,30));
}


// Projectiles trajectory
void Projectile::goUp()
{
    scrollCounter -= 25;
    setPos(x(), y() - 70);
    if(y() < scrollCounter - 875/2){
        scene()->removeItem(this);
        delete this;
    }
}

void Projectile::goUpTimer(QTimer* timer, qint16 scrollCounter)
{
    this->scrollCounter = scrollCounter;
    connect(timer, SIGNAL(timeout()), this, SLOT(goUp()));
}
