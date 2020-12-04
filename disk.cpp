#include "disk.h"

Disk::Disk(QObject *parent, QString diskColor) : QObject(parent)
{
    this->diskColor = diskColor;
    path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    setPixmap((QPixmap(path + "/qtproject/pictures/othello/" + diskColor + ".jpg")).scaled(45, 45));
}

void Disk::flipDisk()
{
    if (this->diskColor == "black")
    {
        this->diskColor = "white";
    }
    else
    {
        this->diskColor = "black";
    }
    setPixmap((QPixmap(path + "/qtproject/pictures/othello/" + diskColor + ".jpg")).scaled(45, 45));
}
