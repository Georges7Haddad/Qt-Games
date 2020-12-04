#include "user.h"

User::User()
{

}

User::User(QString username)
{
    // Store json file in string dataString
    QFile* jsonFile = new QFile();
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    jsonFile->setFileName(path + "/qtproject/usersData.json");
    jsonFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QString dataString;
    dataString = jsonFile->readAll();
    jsonFile->close();

    // Extract userDict given the username of the user
    QJsonDocument dataJsonDocument = QJsonDocument::fromJson(dataString.toUtf8());
    QJsonObject dataDict = dataJsonDocument.object();
    QJsonObject userDict = dataDict[username].toObject();

    // Initialize member variables
    this->username = username;
    password = userDict["password"].toString();
    lastName = userDict["lastName"].toString();
    firstName = userDict["firstName"].toString();
    dateOfBirth = userDict["dateOfBirth"].toString();
    mail = userDict["mail"].toString();
    gender = userDict["gender"].toString();
    profileFileName = userDict["profileFileName"].toString();
    game1Best = userDict["game1Best"].toString();
    game2Best = userDict["game2Best"].toString();
}
