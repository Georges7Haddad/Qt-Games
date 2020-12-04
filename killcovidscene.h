#ifndef KILLCOVIDSCENE_H
#define KILLCOVIDSCENE_H

#include <QGraphicsScene>
#include <QLabel>
#include "virus.h"
#include "doctor.h"

class KillCovidScene : public QGraphicsScene
{
    Q_OBJECT
public:
    KillCovidScene(QString username = "Guest", qint16 gameSpeed = 600, bool infinite = false);
    QString username;
    bool infinite;
    Doctor* doctor;
    void setViruses();
    QList<Virus*> viruses;
    QList<Virus*> virusesToRemove;

    qint8 missedOrCollisionMax;
    void getGameDetails();
    qint8 missedOrCollisionCounter;
    
    qint8 killedVirusesCounter;

    qint8 smallVirusScore;
    qint8 smallVirusCounter;
    qint8 mediumVirusCounter;
    qint8 mediumVirusScore;
    qint8 largeVirusCounter;
    qint8 largeVirusScore;
    qint16 totalScore;
    qint16 winningScore;

    QLabel* scoreLabel;
    QGraphicsProxyWidget* scoreLabelProxy;
    QLabel* livesLabel;
    QGraphicsProxyWidget* livesLabelProxy;

    qint16 scrollCounter;
    QTimer* scrollTimer;
    qint16 gameSpeed;

    QTimer* collisionTimer;
signals:
public slots:
    void createProjectile();
    void collision();
    void removeViruses();
    void autoScroll();
    void missedViruses();
};

#endif // KILLCOVIDSCENE_H
