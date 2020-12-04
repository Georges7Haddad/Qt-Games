#ifndef OTHELLOSCENE_H
#define OTHELLOSCENE_H

#include <QGraphicsScene>
#include <QtWidgets>
#include <QWidget>
#include <QGraphicsEllipseItem>
#include "disk.h"
#include "WelcomeWidget.h"

class OthelloScene : public QGraphicsScene
{
    Q_OBJECT
public:
    OthelloScene(int timeLimit = 900);
    void setLines();
    QString diskColor;
    qint16 tileSize;
    qint16 blackDisksCounter;
    qint16 whiteDisksCounter;
    QLabel* blackDisksCountLabel;
    QLabel* whiteDisksCountLabel;
    QLabel* turnLabel;
    QLabel* placedPositionLabel;
    QVBoxLayout* boxLayout;
    QPushButton* exitGameButton;
    int posMatrix[9][9] = {{0}};
    Disk* diskMatrix[9][9];
    QList<QGraphicsEllipseItem*> ellipseList;

    int timeLimit;
    QTimer* player1Timer;
    int player1TimerCount;
    QLabel* player1TimerLabel;
    QTimer* player2Timer;
    int player2TimerCount;
    QLabel* player2TimerLabel;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    int getColorInt(QString color);
    int getOppositeColorInt(QString color);
    int getCoordFromScreenPos(int position);
    int getScreenPosFromCoord(int coord);
    void flipDisk(int x, int y);
    bool availableTiles();
    bool verticalCheck(QString diskColor, int i, int j);
    bool horizontalCheck(QString diskColor, int i, int j);
    bool diagonalCheck(QString diskColor, int i, int j);
    bool verticalCheckReplace(QString diskColor, int i, int j);
    bool horizontalCheckReplace(QString diskColor, int i, int j);
    bool diagonalCheckReplace(QString diskColor, int i, int j);
    void endGameHandler();

signals:
public slots:
    void exitGame();
    void updateTimersPlayer1();
    void updateTimersPlayer2();
};

#endif // OTHELLOSCENE_H
