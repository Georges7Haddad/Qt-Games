#ifndef USER_H
#define USER_H
#include<QWidget>
#include <QtWidgets>

class User
{
public:
    User();
    User(QString username);
    QString username;
    QString password;
    QString firstName;
    QString lastName;
    QString dateOfBirth;
    QString mail;
    QString gender;
    QString profileFileName;
    QString game1Best;
    QString game2Best;
};

#endif // USER_H
