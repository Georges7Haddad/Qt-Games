#include "game2levelwidget.h"
#include "othelloscene.h"
#include "welcomewidget.h"

Game2LevelWidget::Game2LevelWidget(QWidget *parent) : QWidget(parent)
{    
    levelLabel = new QLabel("Choose your level");
    easyButton = new QPushButton("30 Minutes");
    mediumButton = new QPushButton("15 Minutes");
    hardButton = new QPushButton("7 Minutes");
    backButton = new QPushButton("Main Menu");

    designLayout();

    // SIGNALS
    QObject::connect(backButton, SIGNAL(clicked(bool)), this, SLOT(goBack()));
    connect(easyButton, SIGNAL(clicked(bool)), this, SLOT(startEasy()));
    connect(mediumButton, SIGNAL(clicked(bool)), this, SLOT(startMedium()));
    connect(hardButton, SIGNAL(clicked(bool)), this, SLOT(startHard()));
}

void Game2LevelWidget::designLayout()
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

    verticalLayout->addWidget(backButton);
//    verticalLayout->setAlignment(backButton, Qt::AlignCenter);

    setLayout(verticalLayout);
    setFixedSize(400, 400);

}

void Game2LevelWidget::startEasy()
{
    // 30 minutes
    OthelloScene* game2scene = new OthelloScene(1800);
    this->close();
    QGraphicsView* view = new QGraphicsView(game2scene);
    view->setFixedSize(1000, 900);

    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    view->show();
    delete this;
}

void Game2LevelWidget::startMedium()
{
    // 15 minutes
    OthelloScene* game2scene = new OthelloScene(900);
    this->close();
    QGraphicsView* view = new QGraphicsView(game2scene);
    view->setFixedSize(1000, 900);

    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    view->show();
    delete this;
}

void Game2LevelWidget::startHard()
{
    // 7 minutes
    OthelloScene* game2scene = new OthelloScene(420);
    this->close();
    QGraphicsView* view = new QGraphicsView(game2scene);
    view->setFixedSize(1000, 900);

    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    view->show();
    delete this;
}

void Game2LevelWidget::goBack()
{
    WelcomeWidget* welcomePage = new WelcomeWidget();
    this->close();
    welcomePage->show();
    delete this;
}


