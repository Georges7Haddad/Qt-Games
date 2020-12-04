#include "killcovidscene.h"
#include "welcomewidget.h"
#include "gameoverwidget.h"
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSound>

KillCovidScene::KillCovidScene(QString username, qint16 gameSpeed, bool infinite)
{
    this->username = username;
    this->infinite = infinite;
    missedOrCollisionCounter = 0;
    killedVirusesCounter = 0;
    smallVirusCounter = 0;
    mediumVirusCounter = 0;
    largeVirusCounter = 0;
    totalScore = 0;
    getGameDetails();

    // Scrolling settings
    scrollCounter = 9600;
    scrollTimer = new QTimer();
    this->gameSpeed = gameSpeed;
    scrollTimer->start(gameSpeed);

    // Score Label
    if (infinite == false)
        scoreLabel = new QLabel("Goal: " + QString::number(winningScore) + "\nScore: " + QString::number(0));
    else
        scoreLabel = new QLabel("Score: " + QString::number(0));
    scoreLabel->setFixedWidth(70);
    scoreLabel->setAttribute(Qt::WA_TranslucentBackground);
    scoreLabelProxy = addWidget(scoreLabel);
    scoreLabelProxy->setPos(10, scrollCounter - 775);

    // Lives Label
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    QPixmap img(path + "/qtproject/pictures/killcovid/heart3.png");
    livesLabel = new QLabel(QString::number(3));
    livesLabel->setAttribute(Qt::WA_TranslucentBackground);
    livesLabel->setPixmap(img.scaled(60, 20));
    livesLabelProxy = addWidget(livesLabel);
    livesLabelProxy->setPos(10, scrollCounter - 450);

    // Doctor Settings
    doctor = new Doctor();
    addItem(doctor);
    doctor->setFlag(Doctor::ItemIsFocusable);
    doctor->setFocus();
    doctor->goUpTimer(scrollTimer);

    setViruses();

    // Collision Timer
    collisionTimer = new QTimer();
    collisionTimer->start(10);

    // Timer to remove killed viruses
    QTimer* virusesTimer = new QTimer();
    virusesTimer->start(2000);

    // Scene settings
    QPixmap background(path + "/qtproject/pictures/killcovid/background.png");
    this->setBackgroundBrush(QBrush(background.scaled(350, 4096)));
    setSceneRect(0, 0, 350, 10000);

    // SIGNALS
    connect(doctor->launchButton, SIGNAL(clicked(bool)), this, SLOT(createProjectile()));
    connect(virusesTimer, SIGNAL(timeout()), this, SLOT(removeViruses()));
    connect(collisionTimer, SIGNAL(timeout()), this, SLOT(collision()));
    connect(collisionTimer, SIGNAL(timeout()), this, SLOT(missedViruses()));
    connect(scrollTimer, SIGNAL(timeout()), this, SLOT(autoScroll()));
}

// Auto scroll over the scene
void KillCovidScene::autoScroll()
{  
    // When a player kills more viruses, the game's speed increases
    if (killedVirusesCounter > 10){
        scrollCounter -= 25;
        views().first()->centerOn(QPoint(175, scrollCounter));
    }

    if (killedVirusesCounter >= 5 && killedVirusesCounter < 10){
        scrollCounter -= 25;
        views().first()->centerOn(QPoint(175, scrollCounter));
    }

    if (killedVirusesCounter < 5){
        scrollCounter -= 25;
        views().first()->centerOn(QPoint(175, scrollCounter));
    }

    // Keeps labels at the appropriate postition
    scoreLabelProxy->setPos(10, scrollCounter - 425);
    livesLabelProxy->setPos(10, scrollCounter - 400);
}

void KillCovidScene::createProjectile()
{
    Projectile* projectile = new Projectile();
    projectile->setPos(this->doctor->x() + 30, this->doctor->y() - 60);
    addItem(projectile);
    projectile->goUpTimer(scrollTimer, scrollCounter);
}

void KillCovidScene::setViruses()
{
    // Store json file in string dataString
    QFile* jsonFile = new QFile();
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    jsonFile->setFileName(path + "/qtproject/game1Data.json");
    jsonFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QString dataString;
    dataString = jsonFile->readAll();
    jsonFile->close();

    // Extract dataDict from the dataString
    QJsonDocument dataJsonDocument = QJsonDocument::fromJson(dataString.toUtf8());
    QJsonObject dataDict = dataJsonDocument.object();
    dataDict = dataDict["virusesPositions"].toObject();

    // Creating viruses at the correct positions with the correct sizes
    foreach (QString key, dataDict.keys()) {
        QJsonArray array = dataDict[key].toArray();

        Virus* virus = new Virus(nullptr, array[2].toInt());
        virus->setPos(array[0].toInt(), array[1].toInt());
        viruses.append(virus);
        addItem(virus);
    }
}

void KillCovidScene::collision()
{
    // Game Over
    if (missedOrCollisionCounter == missedOrCollisionMax)
    {
        ++missedOrCollisionCounter;
        QString gameOverMessage = "Game Over \nYou Scored " + QString::number(totalScore);
        GameOverWidget* gameOverPage = new GameOverWidget(nullptr, gameOverMessage, username, totalScore, gameSpeed, infinite);
        gameOverPage->show();
        scrollTimer->stop();
        delete views().first();
    }

    // Game Won
    if (infinite == false && totalScore == winningScore){
        collisionTimer->stop();
        QString gameOverMessage = "Game Won \nYou Scored " + QString::number(totalScore);
        GameOverWidget* gameOverPage = new GameOverWidget(nullptr, gameOverMessage, username, totalScore, gameSpeed, infinite);
        gameOverPage->show();
        scrollTimer->stop();
        delete views().first();
    }

    // For each virus, we check if the virus bumped into something else
    foreach (Virus* virus, viruses) {
        for(QGraphicsItem* item: collidingItems(virus))
         {
            // Bumped into projectile
            if (item != doctor){
                QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
                QSound::play(path + "/qtproject/sounds/punch.wav");
                // Removing virus from scene, deleting it and removing from the list of active viruses
                removeItem(item);
                delete item;
                viruses.removeOne(virus);

                // Setting smashed virus picture
                virus->setPixmap((QPixmap(path + "/qtproject/pictures/killcovid/deadVirus.png")).scaled(50, 50));

                // Add virus to smashed viruses to be removed after a bit of time
                virusesToRemove.append(virus);

                // Increasing Score
                if(virus->size == 30){
                    ++smallVirusCounter;
                    totalScore = (infinite == false && (smallVirusScore + totalScore) > winningScore) ? totalScore : smallVirusScore + totalScore;
                }
                if(virus->size == 50){
                    ++mediumVirusCounter;
                    totalScore = (infinite == false && (mediumVirusScore + totalScore) > winningScore) ? totalScore : mediumVirusScore + totalScore;
                }
                if(virus->size == 70){
                    ++largeVirusCounter;
                    totalScore = (infinite == false && (largeVirusScore + totalScore) > winningScore) ? totalScore : largeVirusScore + totalScore;

                }
                scoreLabel->setText("Score: " + QString::number(totalScore));

                // Increment killed viruses count and check counter for game speed
                ++killedVirusesCounter;
                if (killedVirusesCounter > 10)
                    scrollTimer->setInterval(gameSpeed/4);

                if (killedVirusesCounter >= 5 && killedVirusesCounter < 10)
                    scrollTimer->setInterval(gameSpeed/2);
            }
            // Bumped into doctor
            else{
                QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
                QSound::play(path + "/qtproject/sounds/cough.wav");
                ++missedOrCollisionCounter;
                viruses.removeOne(virus);
                removeItem(virus);
                delete virus;
                if (3 - missedOrCollisionCounter == 2){
                    QPixmap img(path + "/qtproject/pictures/killcovid/heart2.png");
                    livesLabel->setPixmap(img.scaled(40, 20));
                }
                if (3 - missedOrCollisionCounter == 1){
                    QPixmap img2(path + "/qtproject/pictures/killcovid/heart1.png");
                    livesLabel->setPixmap(img2.scaled(20, 20));
                }
            }
        }

    }
}

// Removing smashed viruses
void KillCovidScene::removeViruses()
{
    foreach (Virus* virus, virusesToRemove) {
        removeItem(virus);
        virusesToRemove.removeOne(virus);
        delete virus;
    }
}

// Handling missed viruses
void KillCovidScene::missedViruses()
{
    foreach (Virus* virus, viruses) {
        if(virus->y() > scrollCounter + 875/2){
            QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
            QSound::play(path + "/qtproject/sounds/cough.wav");
            removeItem(virus);
            viruses.removeOne(virus);
            delete virus;
            ++missedOrCollisionCounter;
            if (3 - missedOrCollisionCounter == 2){
                QPixmap img(path + "/qtproject/pictures/killcovid/heart2.png");
                livesLabel->setPixmap(img.scaled(40, 20));
            }
            if (3 - missedOrCollisionCounter == 1){
                QPixmap img2(path + "/qtproject/pictures/killcovid/heart1.png");
                livesLabel->setPixmap(img2.scaled(20, 20));
            }

        }
    }
}

void KillCovidScene::getGameDetails()
{
    // Store json file in string dataString
    QFile* jsonFile = new QFile();
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    jsonFile->setFileName(path + "/qtproject/game1Data.json");
    jsonFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QString dataString;
    dataString = jsonFile->readAll();
    jsonFile->close();

    // Extracting important details about the game
    QJsonDocument dataJsonDocument = QJsonDocument::fromJson(dataString.toUtf8());
    QJsonObject dataDict = dataJsonDocument.object();
    missedOrCollisionMax = dataDict["missedOrCollisionMax"].toInt();
    smallVirusScore = dataDict["smallVirusScore"].toInt();
    mediumVirusScore = dataDict["mediumVirusScore"].toInt();
    largeVirusScore = dataDict["largeVirusScore"].toInt();
    winningScore = dataDict["winningScore"].toInt();
}
