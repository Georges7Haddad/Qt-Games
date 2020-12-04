#include "doctor.h"
#include "killcovidscene.h"
#include <QDir>
#include <QSound>

Doctor::Doctor(QObject *parent) : QObject(parent)
{
    launchButton = new QPushButton();

    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    setPixmap((QPixmap(path + "/qtproject/pictures/killcovid/doctor.png")).scaled(100, 100)); // Removed path + ... and it worked for me
    setPos(175, 9875);

    // Add delay to launching projectiles
    QTimer* timer = new QTimer();
    timer->start(1200);
    connect(timer, SIGNAL(timeout()), this, SLOT(acitvateLaunchButton()));
}

void Doctor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Right)
        setPos(this->x() + 25, this->y());

    if (event->key() == Qt::Key_Left)
        setPos(this->x() - 25, this->y());

    if (event->key() == Qt::Key_Up)
        setPos(this->x(), this->y() - 25);

    if (event->key() == Qt::Key_Down)
        setPos(this->x(), this->y() + 25);

    if (event->key() == Qt::Key_Space)
    {
        QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
        if (launchButton->isEnabled())
            QSound::play(path + "/qtproject/sounds/gunshot.wav");
        launchButton->click();
        launchButton->setDisabled(true);
    }
}

// Enabling launch button, used to add delay between projectiles
void Doctor::acitvateLaunchButton()
{
    launchButton->setDisabled(false);
}

// Screen is scrolling up, so we need to keep up with it
void Doctor::goUp()
{
    setPos(x(), y() - 25);
}

void Doctor::goUpTimer(QTimer* timer)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(goUp()));
}
