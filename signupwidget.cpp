#include "signupwidget.h"
#include "loginwidget.h"
#include "welcomewidget.h"

SignUpWidget::SignUpWidget(QWidget *parent) : QWidget(parent)
{
    // First name, Last name, and their layout
    firstNameLabel = new QLabel("First name <sup>*</sup>: ");
    firstName = new QLineEdit();

    lastNameLabel = new QLabel("Last name <sup>*</sup>: ");
    lastName = new QLineEdit();

    // Email
    emailLabel = new QLabel("Email Address <sup>*</sup>: ");
    emailAddress = new QLineEdit();

    //Password Instruction Label
    passwordInstruction = new QLabel("Your password should consist of at least 8 characters and\ncontain at least one number, upper and lower case letters.");
    passwordInstruction->setFixedSize(800, 30);

    // Genders and their layout
    genderLabel = new QLabel("Gender :");
    male = new QRadioButton("Male");
    female = new QRadioButton("Female");
    other = new QRadioButton("Other");

    genderLayout = new QVBoxLayout();

    // Username
    usernameLabel = new QLabel("Username <sup>*</sup>: ");
    username = new QLineEdit();

    // Password, its confirmation, and setting them as black dots when typed
    passwordLabel = new QLabel("Password <sup>*</sup>: ");
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);
    confirmPasswordLabel = new QLabel("Confirm password <sup>*</sup>: ");
    ConfirmPassword = new QLineEdit();
    ConfirmPassword->setEchoMode(QLineEdit::Password);

    // Date of birth
    dateOfBirthLabel = new QLabel("Date of birth: ");
    dateOfBirth = new QDateEdit();

    // Profile Picture
    addProfile = new QPushButton("Add Profile Picture");
    profilePicture = new QFileDialog();
    profilePicture->hide();

    // Create account button
    createButton = new QPushButton("Create account");
    createButton->setFixedSize(300, 35);
    createButton->setStyleSheet("background-color:green;");

    // Fields Check Label
    errorLabel = new QLabel();

    // Mandatory fields label
    starsLabel = new QLabel("* Fields are mandatory.");

    // Back Button
    backButton = new QPushButton("Back");
    backButton->setFixedSize(40, 25);

    // Layouts for the whole page
    verticalLayout = new QVBoxLayout();
    gridLayout = new QGridLayout();

    // Setting the layouts
    designLayout();

    // SIGNALS
    QObject::connect(createButton, SIGNAL(clicked(bool)), this, SLOT(createEntry()));
    QObject::connect(backButton, SIGNAL(clicked(bool)), this, SLOT(goBack()));
    QObject::connect(addProfile, SIGNAL(clicked(bool)), this, SLOT(showProfileDialog()));
}

void SignUpWidget::showProfileDialog()
{
    filePath = profilePicture->getOpenFileName();
}

void SignUpWidget::designLayout()
{
    // Gender Layout
    genderLayout->addWidget(female);
    genderLayout->addWidget(male);
    genderLayout->addWidget(other);

    // Grid Layout
    gridLayout->setVerticalSpacing(20);
    gridLayout->setHorizontalSpacing(10);
    gridLayout->addItem(new QSpacerItem(70, 20), 0, 0);
    gridLayout->addWidget(firstNameLabel, 1, 1);
    gridLayout->addWidget(firstName, 1, 2);
    gridLayout->addWidget(lastNameLabel, 2, 1);
    gridLayout->addWidget(lastName, 2, 2);
    gridLayout->addItem(new QSpacerItem(55,30),3,3);
    gridLayout->addWidget(emailLabel,3,1);
    gridLayout->addWidget(emailAddress,3,2);
    gridLayout->addWidget(usernameLabel,4,1);
    gridLayout->addWidget(username,4,2);
    gridLayout->addWidget(passwordLabel,5,1);
    gridLayout->addWidget(password,5,2);
    gridLayout->addWidget(confirmPasswordLabel,6,1);
    gridLayout->addWidget(ConfirmPassword,6,2);
    gridLayout->addWidget(passwordInstruction, 7, 1);
    gridLayout->addWidget(genderLabel,8,1);
    gridLayout->addItem(genderLayout,8,2);
    gridLayout->addWidget(dateOfBirthLabel,9,1);
    gridLayout->addWidget(dateOfBirth,9,2);
    gridLayout->addItem(new QSpacerItem(500, 0), 9, 3);
    gridLayout->addItem(new QSpacerItem(300, 0), 9, 4);
    gridLayout->addWidget(addProfile, 10, 2);
    gridLayout->addWidget(createButton,11,2);

    // Vertical Layout
    verticalLayout->addWidget(backButton);
    verticalLayout->addWidget(starsLabel);
    verticalLayout->insertSpacing(1,10);
    verticalLayout->addItem(gridLayout);
    verticalLayout->addWidget(errorLabel);

    setLayout(verticalLayout);
    setFixedSize(800, 800);
}

bool SignUpWidget::checkEntries()
{
    bool at = false;

    // Checking if the email address is valid
    for(int i = 0; i < emailAddress->text().length();i++)
    {
        if (emailAddress->text()[i] == '@')
        {
            at = true;
            break;
        }
    }

    if (firstName->text().isEmpty())
    {
        errorLabel->setText("Kindly provide your first name");
        return false;
    }
    else if (lastName->text().isEmpty())
    {
        errorLabel->setText("Kindly provide your last name");
        return false;
    }
    else if(username->text().isEmpty())
    {
        errorLabel->setText("Kindly provide a username");
        return false;
    }
    else if(!at)
    {
        errorLabel->setText("Please enter a valid mail address");
        return false;
    }

    return true;
}

bool SignUpWidget::passwordIsValid()
{
    bool size = true;
    bool capital = false;
    bool numbers = false;

    if ((password->text()).length() < 8)
    {
        errorLabel->setText("Password must contain at least 8 characters");
        size = false;
    }

    for (int i =0; i<=password->text().length();i++)
    {
        if (password->text()[i] >= 'A' && password->text()[i] <= 'Z')
            capital = true;
        if (password->text()[i] >= '0' && password->text()[i] <= '9')
            numbers = true;
    }

    if(!capital)
        errorLabel->setText("Password must include at least 1 capital letter");

    if(!numbers)
        errorLabel->setText("Password must include at least 1 number");

    return (size && capital && numbers);
}

bool SignUpWidget::confirmPassword()
{
    if(password->text() != ConfirmPassword->text())
    {
        errorLabel->setText("Password does not match confirmation");
        return false;
    }
    return true;
}

void SignUpWidget::createEntry()
{
    if (!(checkEntries() and passwordIsValid() and confirmPassword()))
        return;

    // Store json file in string dataString
    QFile* jsonFile = new QFile();
    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    jsonFile->setFileName(path + "/qtproject/usersData.json");
    jsonFile->open(QIODevice::ReadWrite | QIODevice::Text);
    QString dataString;
    dataString = jsonFile->readAll();

    // Extract all users dicts from the dataString
    QJsonDocument dataJsonDocument = QJsonDocument::fromJson(dataString.toUtf8());
    QJsonObject dataDict = dataJsonDocument.object();

    // Checks if username taken
    foreach (QJsonValue dict, dataDict) {
        QJsonObject user = dict.toObject();
        if(username->text() == user["username"].toString())
        {
            errorLabel->setText("This username is taken, please provide another one");
            return;
        }
    }

    // Handling gender
    QString gender;
    if (male->isChecked())
        gender += "male";
    else if (female->isChecked())
        gender += "female";
    else
        gender = "other";

    // Get the uploaded image
    QPixmap pic(filePath);

    // Get the picture extension and save it as "username.extension"
    QStringList pathString = filePath.split(".");
    QString pictureName = username->text() +"." + pathString[pathString.length() - 1];
    QFile file(path + "/qtproject/pictures/profilePictures/" + pictureName);
    file.open(QIODevice::WriteOnly);
    pic.save(&file);
    file.close();

    // Create new user dict
    QJsonObject entry;
    entry.insert("dateOfBirth", dateOfBirth->date().toString("dd/MM/yyyy"));
    entry.insert("lastName", lastName->text());
    entry.insert("firstName", firstName->text());
    entry.insert("password", password->text());
    entry.insert("username", username->text());
    entry.insert("mail", emailAddress->text());
    entry.insert("gender", gender);
    entry.insert("profileFileName", pictureName);
    QJsonDocument dict(entry);

    // Add new user dict to the rest of dicts
    dataDict.insert(username->text(), entry);
    QJsonDocument doc(dataDict);

    // Clear file then add back the updated dict of users
    jsonFile->resize(0);
    jsonFile->write(doc.toJson());
    jsonFile->close();

    // Go to the welcome page
    WelcomeWidget* welcomePage = new WelcomeWidget(nullptr, username->text());
    this->close();
    welcomePage->show();
}

void SignUpWidget::goBack()
{
    LoginWidget* signupPage = new LoginWidget(nullptr);
    this->close();
    delete this;
    signupPage->show();
}






