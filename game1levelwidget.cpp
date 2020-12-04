#include "game1levelwidget.h"
#include "killcovidscene.h"
#include "welcomewidget.h"

Game1LevelWidget::Game1LevelWidget(QWidget *parent, QString username) : QWidget(parent)
{
    this->username = username;
    levelLabel = new QLabel("Choose your level");
    easyButton = new QPushButton("Easy");
    mediumButton = new QPushButton("Medium");
    hardButton = new QPushButton("Hard");
    infiniteButton = new QPushButton("Infinite");
    backButton = new QPushButton("Main Menu");

    designLayout();

    // SIGNALS

    QObject::connect(backButton, SIGNAL(clicked(bool)), this, SLOT(goBack()));
    connect(easyButton, SIGNAL(clicked(bool)), this, SLOT(startEasy()));
    connect(mediumButton, SIGNAL(clicked(bool)), this, SLOT(startMedium()));
    connect(hardButton, SIGNAL(clicked(bool)), this, SLOT(startHard()));
    connect(infiniteButton, SIGNAL(clicked(bool)), this, SLOT(startInfinite()));
}

void Game1LevelWidget::designLayout()
{
    QVBoxLayout* verticalLayout = new QVBoxLayout();

    verticalLayout->addWidget(levelLabel);
    verticalLayout->setAlignment(levelLabel, Qt::AlignCenter);

    verticalLayout->addWidget(easyButton);
    verticalLayout->setAlignment(easyButton, Qt::AlignCenter);

    verticalLayout->addWidget(mediumButton);
    verticalLayout->setAlignment(mediumButton, Qt::AlignCenter);

    verticalLayout->addWidget(hardButton);
    verticalLayout->setAlignment(hardButton, Qt::AlignCenter);


    verticalLayout->addWidget(infiniteButton);
    verticalLayout->setAlignment(infiniteButton, Qt::AlignCenter);

    verticalLayout->addWidget(backButton);
//    verticalLayout->setAlignment(backButton, Qt::AlignCenter);

    setLayout(verticalLayout);
    setFixedSize(400, 400);

}

void Game1LevelWidget::startEasy()
{
    KillCovidScene* game1scene = new KillCovidScene(username, 600);
    this->close();
    QGraphicsView* view = new QGraphicsView(game1scene);
    view->setFixedSize(350, 875);

    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->centerOn(QPoint(175, 10000));

    view->show();
}

void Game1LevelWidget::startMedium()
{
    KillCovidScene* game1scene = new KillCovidScene(username, 550);
    this->close();
    QGraphicsView* view = new QGraphicsView(game1scene);
    view->setFixedSize(350, 875);

    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->centerOn(QPoint(175, 10000));

    view->show();
    delete this;
}

void Game1LevelWidget::startHard()
{
    KillCovidScene* game1scene = new KillCovidScene(username, 500);
    this->close();
    QGraphicsView* view = new QGraphicsView(game1scene);
    view->setFixedSize(350, 875);

    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->centerOn(QPoint(175, 10000));

    view->show();
    delete this;
}

void Game1LevelWidget::startInfinite()
{
    KillCovidScene* game1scene = new KillCovidScene(username, 550, true);
    this->close();
    QGraphicsView* view = new QGraphicsView(game1scene);
    view->setFixedSize(350, 875);

    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->centerOn(QPoint(175, 10000));

    view->show();
    delete this;
}

void Game1LevelWidget::goBack()
{
    WelcomeWidget* welcomePage = new WelcomeWidget(nullptr, username);
    this->close();
    welcomePage->show();
    delete this;
}


