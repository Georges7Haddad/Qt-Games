#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QWidget>
#include <QtWidgets>

class SignUpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SignUpWidget(QWidget *parent = nullptr);
    QLabel* firstNameLabel;
    QLineEdit* firstName;
    QLabel* lastNameLabel;
    QLineEdit* lastName;
    QLabel* picture;
    QLabel* emailLabel;
    QLineEdit* emailAddress;
    QLabel* passwordInstruction;
    QLabel* errorLabel;
    QLabel* starsLabel;
    QLabel* genderLabel;
    QRadioButton* male;
    QRadioButton* female;
    QRadioButton* other;
    QVBoxLayout* genderLayout;
    QLabel* usernameLabel;
    QLineEdit* username;
    QLabel* passwordLabel;
    QLineEdit* password;
    QLabel* confirmPasswordLabel;
    QLineEdit* ConfirmPassword;
    QLabel* dateOfBirthLabel;
    QDateEdit* dateOfBirth;
    QPushButton* addProfile;
    QFileDialog* profilePicture;
    QPushButton* backButton;
    QPushButton* createButton;
    QString filePath;

    QVBoxLayout* verticalLayout;
    QGridLayout* gridLayout;

    void designLayout();

signals:

public slots:
    void goBack();
    bool checkEntries();
    bool passwordIsValid();
    bool confirmPassword();
    void createEntry();
    void showProfileDialog();

};

#endif // SIGNUPWIDGET_H

