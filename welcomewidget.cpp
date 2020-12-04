#include "welcomewidget.h"
#include "loginwidget.h"
#include "killcovidscene.h"
#include "game1levelwidget.h"
#include "othelloscene.h"
#include "game2levelwidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent, QString username) : QWidget(parent)
{
    user = User(username);

    welcomeLabel = new QLabel("Welcome " + user.username);
    verticalLayout = new QVBoxLayout();
    logoutButton = new QPushButton("Logout");
    deleteUserButton = new QPushButton("Delete Account");

    // Game 1 Button + Hishscore and User's best
    game1Button = new QPushButton("Play KILL COVID 19");
    game1Label = new QLabel("High Score: " + getGame1Highscore());
    if (!user.game1Best.isNull())
         game1Label->setText(game1Label->text() + "\nPersonal Best: " + user.game1Best);

    // Game 2 Button + Hishscore and User's best
    game2Button = new QPushButton("Play Reversi (Othello)");
    game2Label = new QLabel("High Score: " + getGame2Highscore());
    if (!user.game2Best.isNull())
         game2Label->setText(game2Label->text() + "\nPersonal Best: " + user.game2Best);

    // Handling Guest Image
    if(user.username == "Guest")
        user.profileFileName = "Guest.jpg";

    // Profile Picture
    profilePicture = new QLabel();
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    QPixmap img(path + "/qtproject/pictures/profilePictures/" + user.profileFileName);
    profilePicture->setPixmap(img.scaled(100, 100));

    designLayout();

    // SIGNALS
    QObject::connect(logoutButton, SIGNAL(clicked(bool)), this, SLOT(logout()));
    QObject::connect(deleteUserButton, SIGNAL(clicked(bool)), this, SLOT(deleteUser()));
    QObject::connect(game1Button, SIGNAL(clicked(bool)), this, SLOT(startKillCovid()));
    QObject::connect(game2Button, SIGNAL(clicked(bool)), this, SLOT(startOthello()));
}

void WelcomeWidget::designLayout(){
    verticalLayout->addWidget(logoutButton);

    // Handling Guest
    if(user.username != "Guest")
        verticalLayout->addWidget(deleteUserButton);


    verticalLayout->addWidget(welcomeLabel);
    verticalLayout->addWidget(profilePicture);

    // Handling Birthdays
    if (user.dateOfBirth.remove(5, 5) == QDate::currentDate().toString("dd/MM")){
        birthdayLabel = new QLabel("HAPPY BIRTHDAY");
        verticalLayout->addWidget(birthdayLabel);
    }
    verticalLayout->addWidget(game1Button);
    verticalLayout->addWidget(game1Label);
    verticalLayout->addWidget(game2Button);
    verticalLayout->addWidget(game2Label);

    setLayout(verticalLayout);
    setFixedSize(800, 800);
}

void WelcomeWidget::logout()
{
    LoginWidget* signupPage = new LoginWidget(nullptr);
    this->close();
    delete this;
    signupPage->show();
}

void WelcomeWidget::deleteUser()
{
    // Store json file in string dataString
    QFile* jsonFile = new QFile();
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    jsonFile->setFileName(path + "/qtproject/usersData.json");
    jsonFile->open(QIODevice::ReadWrite | QIODevice::Text);
    QString dataString;
    dataString = jsonFile->readAll();

    // Extract all users dicts from the dataString and remove user
    QJsonDocument dataJsonDocument = QJsonDocument::fromJson(dataString.toUtf8());
    QJsonObject dataDict = dataJsonDocument.object();
    dataDict.remove(user.username);
    QJsonDocument doc(dataDict);

    // Clear file then add back the updated dict of users
    jsonFile->resize(0);
    jsonFile->write(doc.toJson());
    jsonFile->close();

    // Delete Profile Picture
    QFile file(path + "/qtproject/pictures/profilePictures/" +  user.profileFileName);
    file.remove();

    // Return to login page
    LoginWidget* loginPage = new LoginWidget();
    this->close();
    loginPage->show();
}

void WelcomeWidget::startKillCovid()
{
    Game1LevelWidget* game1level = new Game1LevelWidget(nullptr, user.username);
    this->close();
    game1level->show();
}

void WelcomeWidget::startOthello()
{
    Game2LevelWidget* game2level = new Game2LevelWidget();
    this->close();
    game2level->show();
}

QString WelcomeWidget::getGame1Highscore()
{
    // Store json file in string dataString
    QFile* jsonFile = new QFile();
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    jsonFile->setFileName(path + "/qtproject/game1Data.json");
    jsonFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QString dataString;
    dataString = jsonFile->readAll();
    jsonFile->close();

    // Extract userDict given the username of the user
    QJsonDocument dataJsonDocument = QJsonDocument::fromJson(dataString.toUtf8());
    QJsonObject dataDict = dataJsonDocument.object();
    return (dataDict["bestPlayer"].toString() + ": " + dataDict["highscore"].toString());
}

QString WelcomeWidget::getGame2Highscore()
{
    // Store json file in string dataString
    QFile* jsonFile = new QFile();
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    jsonFile->setFileName(path + "/qtproject/game2Data.json");
    jsonFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QString dataString;
    dataString = jsonFile->readAll();
    jsonFile->close();

    // Extract userDict given the username of the user
    QJsonDocument dataJsonDocument = QJsonDocument::fromJson(dataString.toUtf8());
    QJsonObject dataDict = dataJsonDocument.object();
    return (dataDict["bestPlayer"].toString() + ": " + dataDict["highscore"].toString());
}
