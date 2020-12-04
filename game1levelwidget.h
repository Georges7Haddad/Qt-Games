#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <QWidget>
#include <QtWidgets>

class Game1LevelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Game1LevelWidget(QWidget *parent = nullptr, QString username = "Guest");
    QPushButton* easyButton;
    QPushButton* mediumButton;
    QPushButton* hardButton;
    QPushButton* backButton;
    QPushButton* infiniteButton;
    QLabel* levelLabel;
    QString username;
    void designLayout();

signals:
public slots:
    void startEasy();
    void startMedium();
    void startHard();
    void startInfinite();
    void goBack();

};

#endif // GAMELEVEL_H
