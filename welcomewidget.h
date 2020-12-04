#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QKeyEvent>
#include <user.h>


class WelcomeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeWidget(QWidget *parent = nullptr, QString username = "Guest");
    QLabel* welcomeLabel;
    QLabel* birthdayLabel;
    QVBoxLayout* verticalLayout;
    QPushButton* logoutButton;
    QPushButton* deleteUserButton;

    QPushButton* game1Button;
    QLabel* game1Label;
    QPushButton* game2Button;
    QLabel* game2Label;

    QLabel *profilePicture;
    User user;

    void designLayout();
    QString getGame1Highscore();
    QString getGame2Highscore();

signals:
public slots:
    void logout();
    void deleteUser();
    void startKillCovid();
    void startOthello();
};

#endif // WELCOMEWIDGET_H
