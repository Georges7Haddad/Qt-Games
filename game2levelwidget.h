#ifndef GAME2LEVELWIDGET_H
#define GAME2LEVELWIDGET_H

#include <QWidget>
#include <QtWidgets>

class Game2LevelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Game2LevelWidget(QWidget *parent = nullptr);
    QPushButton* easyButton;
    QPushButton* mediumButton;
    QPushButton* hardButton;
    QPushButton* backButton;
    QLabel* levelLabel;
    void designLayout();

signals:
public slots:
    void startEasy();
    void startMedium();
    void startHard();
    void goBack();
};

#endif // GAME2LEVELWIDGET_H
