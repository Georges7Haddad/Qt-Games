#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H

#include <QWidget>
#include <QtWidgets>

class GameOverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameOverWidget(QWidget *parent = nullptr, QString endGameText = "Game Over", QString username = "Guest", qint16 score = 0, qint16 gameSpeed = 600, bool infinite = false);
    QPushButton* startAgainButton;
    QPushButton* exitGameButton;
    QLabel* endGameLabel;
    QString username;
    qint16 score;
    qint16 gameSpeed;
    bool infinite;
    void updateScoreDatabase();
    void designLayout();

signals:
public slots:
    void startAgain();
    void exitGame();

};

#endif // GAMEOVERWIDGET_H
