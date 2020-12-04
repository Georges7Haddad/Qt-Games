#include "gameoverwidget.h"
#include "welcomewidget.h"
#include "killcovidscene.h"

GameOverWidget::GameOverWidget(QWidget *parent, QString endGameText, QString username, qint16 score, qint16 gameSpeed, bool infinite) : QWidget(parent)
{
    this->username = username;
    this->score = score;
    this->gameSpeed = gameSpeed;
    this->infinite = infinite;
    startAgainButton = new QPushButton("Try Again");
    exitGameButton = new QPushButton("Main Menu");
    endGameLabel = new QLabel(endGameText);

    designLayout();
    updateScoreDatabase();

    // SIGNALS
    connect(startAgainButton, SIGNAL(clicked(bool)), this, SLOT(startAgain()));
    connect(exitGameButton, SIGNAL(clicked(bool)), this, SLOT(exitGame()));
}

void GameOverWidget::designLayout()
{
    QVBoxLayout* verticalLayout = new QVBoxLayout();

    verticalLayout->addWidget(endGameLabel);
    verticalLayout->setAlignment(endGameLabel, Qt::AlignCenter);

    verticalLayout->addWidget(startAgainButton);
    verticalLayout->setAlignment(startAgainButton, Qt::AlignCenter);

    verticalLayout->addWidget(exitGameButton);
    verticalLayout->setAlignment(exitGameButton, Qt::AlignCenter);

    setLayout(verticalLayout);
    setFixedSize(400, 400);
}

void GameOverWidget::exitGame()
{
    WelcomeWidget* welcomePage = new WelcomeWidget(nullptr, username);
    this->close();
    welcomePage->show();
}

void GameOverWidget::startAgain()
{
    KillCovidScene* game1scene = new KillCovidScene(username, gameSpeed, infinite);
    QGraphicsView* view = new QGraphicsView(game1scene);
    view->setFixedSize(350, 875);

    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOn));
    view->centerOn(QPoint(175, 10000));

    this->close();
    view->show();
    delete this;
}

void GameOverWidget::updateScoreDatabase()
{
    // Store game1 json file in string game1DataString
    QFile* game1jsonFile = new QFile();
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    game1jsonFile->setFileName(path + "/qtproject/game1Data.json");
    game1jsonFile->open(QIODevice::ReadWrite | QIODevice::Text);
    QString game1DataString = game1jsonFile->readAll();

    // Extracting the game1 data dict
    QJsonDocument game1DataJsonDocument = QJsonDocument::fromJson(game1DataString.toUtf8());
    QJsonObject game1DataDict = game1DataJsonDocument.object();

    // If current score bigger than highscore, we update it
    if (game1DataDict["highscore"].toString().toInt() < score){
        endGameLabel->setText(endGameLabel->text() + "\nCongratulations on a new GAME BEST");
        game1DataDict.remove("bestPlayer");
        game1DataDict.insert("bestPlayer", username);
        game1DataDict.remove("highscore");
        game1DataDict.insert("highscore", QString::number(score));

        QJsonDocument doc1(game1DataDict);

        // Clear file then add back the updated scores
        game1jsonFile->resize(0);
        game1jsonFile->write(doc1.toJson());
        game1jsonFile->close();
    }

    if (username != "Guest"){
        // Store json file in string usersDataString
        QFile* usersjsonFile = new QFile();
        usersjsonFile->setFileName(path + "/qtproject/usersData.json");
        usersjsonFile->open(QIODevice::ReadWrite | QIODevice::Text);
        QString usersDataString = usersjsonFile->readAll();

        // Extracting important details about the game
        QJsonDocument usersDataJsonDocument = QJsonDocument::fromJson(usersDataString.toUtf8());
        QJsonObject usersDataDict = usersDataJsonDocument.object();
        QJsonObject userDataDict = usersDataDict[username].toObject();

        // If current score is bigger than personal highscore, we upadte it
        if (userDataDict["game1Best"].toString().toInt() < score){
            endGameLabel->setText(endGameLabel->text() + "\nCongratulations on a new PERSONAL BEST");
            userDataDict.remove("game1Best");
            userDataDict.insert("game1Best", QString::number(score));

            usersDataDict.remove(username);
            usersDataDict.insert(username, userDataDict);
            QJsonDocument doc(usersDataDict);

            // Clear file then add back the updated score
            usersjsonFile->resize(0);
            usersjsonFile->write(doc.toJson());
            usersjsonFile->close();
        }
    }
}
