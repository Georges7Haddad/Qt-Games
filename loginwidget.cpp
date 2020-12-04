#include "loginwidget.h"
#include "welcomewidget.h"
#include "user.h"
#include "signupwidget.h"
#include <QJsonParseError>

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{
    pageTitle = new QLabel("LOGIN");
    loginFeedback = new QLabel();

    usernameLabel = new QLabel("Username");
    username = new QLineEdit();
    username->setFixedSize(200, 20);

    passwordLabel = new QLabel("Password");
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);
    password->setFixedSize(200, 20);

    signupLabel = new QLabel("Not registered yet?");
    signupButton = new QPushButton("Sign up");
    signupButton->setFixedSize(60, 35);
    signupButton->setStyleSheet("background-color:green;");
    signupLayout = new QHBoxLayout();

    guestButton = new QPushButton("Play as Guest");
    guestButton->setFixedSize(300, 35);
    guestButton->setStyleSheet("background-color:red;");
    loginButton = new QPushButton("Login");
    loginButton->setFixedSize(300, 35);
    loginButton->setStyleSheet("background-color:blue;");

    verticalLayout = new QVBoxLayout();
    gridLayout = new QGridLayout();

    designLayout();

    // SIGNALS
    QObject::connect(loginButton, SIGNAL(clicked(bool)), this, SLOT(login()));
    QObject::connect(guestButton, SIGNAL(clicked(bool)), this, SLOT(guestLogin()));
    QObject::connect(signupButton, SIGNAL(clicked(bool)), this, SLOT(signup()));
}

void LoginWidget::designLayout()
{
    // Grid Layout
    gridLayout->setVerticalSpacing(10);
    gridLayout->addItem(new QSpacerItem(135, 20), 0, 0);
    gridLayout->addWidget(usernameLabel, 0, 1);
    gridLayout->addWidget(username, 0, 2);
    gridLayout->addItem(new QSpacerItem(240, 20), 0, 3);
    gridLayout->addWidget(passwordLabel, 1, 1);
    gridLayout->addWidget(password, 1, 2);
    gridLayout->addItem(new QSpacerItem(240, 20), 1, 3);
    gridLayout->addWidget(loginButton, 2, 2);
    gridLayout->addItem(new QSpacerItem(240, 0), 2, 3);

    // Register Horizontal Layout
    signupLayout->addWidget(signupLabel);
    signupLayout->addWidget(signupButton);

    // Vertical Layout
    verticalLayout->setSpacing(50);
    verticalLayout->addWidget(pageTitle);
    verticalLayout->setAlignment(pageTitle, Qt::AlignCenter);
    verticalLayout->addItem(gridLayout);
    verticalLayout->addWidget(guestButton);
    verticalLayout->setAlignment(guestButton, Qt::AlignCenter);
    verticalLayout->addItem(signupLayout);
    verticalLayout->setAlignment(signupLayout, Qt::AlignCenter);
    verticalLayout->addWidget(loginFeedback);
    verticalLayout->addStretch();

    setLayout(verticalLayout);
    setFixedSize(800, 800);
}

void LoginWidget::guestLogin()
{
    WelcomeWidget* welcomePage = new WelcomeWidget(nullptr, "Guest");
    this->close();
    delete this;
    welcomePage->show();
}

void LoginWidget::signup()
{
    SignUpWidget* signupPage = new SignUpWidget(nullptr);
    this->close();
    delete this;
    signupPage->show();
}

void LoginWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
        login();
}

void LoginWidget::login()
{
    // Store json file in string dataString
    QFile* jsonFile = new QFile();
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    jsonFile->setFileName(path + "/qtproject/usersData.json");
    jsonFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QString dataString;
    dataString = jsonFile->readAll();
    jsonFile->close();

    // Extract dataDict from the dataString
    QJsonDocument dataJsonDocument = QJsonDocument::fromJson(dataString.toUtf8());
    QJsonObject dataDict = dataJsonDocument.object();

    //Verify if user exists by looping over all users
    bool found = false;
    foreach (QJsonValue dict, dataDict) {
        QJsonObject user = dict.toObject();
        if(username->text() == user["username"].toString() && password->text() == user["password"].toString())
        {
            found = true;
            break;
        }
    }
    if(found){
        loginFeedback->setText("WE'RE LOGGING YOU IN");
        WelcomeWidget* welcomePage = new WelcomeWidget(nullptr, username->text());
        this->close();
        welcomePage->show();
        delete this;
    }
    else
        loginFeedback->setText("USER NOT FOUND PLEASE TRY AGAIN");
}
