#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QtWidgets>

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    QLabel* pageTitle;
    QLabel* loginFeedback;

    QLabel* usernameLabel;
    QLineEdit* username;

    QLabel* passwordLabel;
    QLineEdit* password;

    QLabel* signupLabel;
    QPushButton* signupButton;
    QHBoxLayout* signupLayout;
    QPushButton* loginButton;
    QPushButton* guestButton;

    QGridLayout* gridLayout;
    QVBoxLayout* verticalLayout;

    void designLayout();
    void keyPressEvent(QKeyEvent *event);

signals:
public slots:
    void login();
    void guestLogin();
    void signup();
};

#endif // LOGINWIDGET_H
