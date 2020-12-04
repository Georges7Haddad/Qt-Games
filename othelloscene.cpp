#include "othelloscene.h"

OthelloScene::OthelloScene(int timeLimit)
{
//    for (int i = 1; i < 9; i++) {
//        for (int j = 1; j < 9; j++) {
//            diskMatrix[i][j] = new Disk(nullptr, "t");
//        }
//    }
    // Scene settings
    diskColor = "black";
    tileSize = 80;
    blackDisksCounter = 2;
    whiteDisksCounter = 2;
    exitGameButton = new QPushButton("Main Menu");
    QGraphicsProxyWidget* exitButtonProxy = addWidget(exitGameButton);
    exitButtonProxy->setPos(10, 10);

    QString path = QDir::currentPath().remove(QDir::currentPath().length() - 77, 77);
    this->setBackgroundBrush(QBrush(Qt::green, Qt::Dense4Pattern));
    setSceneRect(0, 0, 1000, 900);
    setLines();
    availableTiles();
    this->timeLimit = timeLimit;

    // Player 1 timer
    player1TimerCount = 0;
    player1TimerLabel = new QLabel("Black Timer: " + QString::number(player1TimerCount));
    player1TimerLabel->setAttribute(Qt::WA_TranslucentBackground);
    player1TimerLabel->setFixedSize(100, 100);
    QGraphicsProxyWidget* player1TimerLabelProxy = new QGraphicsProxyWidget();
    player1TimerLabelProxy = addWidget(player1TimerLabel);
    player1TimerLabelProxy->setPos(800,  400);
    player1Timer = new QTimer();
    player1Timer->start(1000);
    connect(player1Timer, SIGNAL(timeout()), this, SLOT(updateTimersPlayer1()));

    // Player 2 timer
    player2TimerCount = 0;
    player2TimerLabel = new QLabel("White Timer: " + QString::number(player2TimerCount));
    player2TimerLabel->setAttribute(Qt::WA_TranslucentBackground);
    player2TimerLabel->setFixedSize(100, 100);
    QGraphicsProxyWidget* player2TimerLabelProxy = new QGraphicsProxyWidget();
    player2TimerLabelProxy = addWidget(player2TimerLabel);
    player2TimerLabelProxy->setPos(800,  430);
    player2Timer = new QTimer();
    connect(player2Timer, SIGNAL(timeout()), this, SLOT(updateTimersPlayer2()));

    connect(exitGameButton, SIGNAL(clicked(bool)), this, SLOT(exitGame()));
    // Printing the pos matrix for debugging
    for (int i = 1; i < 9; i++) {
        qWarning() << posMatrix[i][1] << posMatrix[i][2] << posMatrix[i][3] << posMatrix[i][4] << posMatrix[i][5] << posMatrix[i][6] <<posMatrix[i][7]<< posMatrix[i][8];
    }
    qWarning() << "\n";
    // Printing the disk matrix for debugging
//    for (int i = 1; i < 9; i++) {
//        qWarning() << diskMatrix[i][1]->diskColor << diskMatrix[i][2]->diskColor << diskMatrix[i][3]->diskColor << diskMatrix[i][4]->diskColor << diskMatrix[i][5]->diskColor << diskMatrix[i][6]->diskColor << diskMatrix[i][7]->diskColor << diskMatrix[i][8]->diskColor;
//    }
//    qWarning() << "\n";
}

void OthelloScene::updateTimersPlayer1()
{
    if (player1TimerCount == timeLimit)
        endGameHandler();
    player1TimerLabel->setText("Black Timer: " + QString::number(++player1TimerCount));
}
void OthelloScene::updateTimersPlayer2()
{
    if (player2TimerCount == timeLimit)
        endGameHandler();
    player2TimerLabel->setText("White Timer: " + QString::number(++player2TimerCount));
}

void OthelloScene::setLines()
{
    // Vertical Lines
    for(int i = 1; i < 9; i++) {
        QLabel* tilesLabel = new QLabel(QString(char(64 + i)));
        tilesLabel->setAttribute(Qt::WA_TranslucentBackground);
        QGraphicsProxyWidget* tilesLabelProxy = new QGraphicsProxyWidget();
        tilesLabelProxy = addWidget(tilesLabel);
        tilesLabelProxy->setPos(i * tileSize + 40, 40);
        addLine(i * tileSize, tileSize, i * tileSize, 9 * tileSize, Qt::SolidLine);
    }
    addLine(9 * tileSize, tileSize, 9 * tileSize, 9 * tileSize, Qt::SolidLine);

    // Horizontal Lines
    for(int i = 1; i < 9; i++) {
        QLabel* tilesLabel = new QLabel(QString::number(i));
        tilesLabel->setAttribute(Qt::WA_TranslucentBackground);
        QGraphicsProxyWidget* tilesLabelProxy = new QGraphicsProxyWidget();
        tilesLabelProxy = addWidget(tilesLabel);
        tilesLabelProxy->setPos(40, i * tileSize + 40);
        addLine(tileSize, i * tileSize, tileSize * 9, i * tileSize, Qt::SolidLine);
    }
    addLine(tileSize, 9 * tileSize, tileSize * 9, 9 * tileSize, Qt::SolidLine);

    // Black Disks Count Label
    blackDisksCountLabel = new QLabel("Black: " + QString::number(blackDisksCounter));
    blackDisksCountLabel->setAttribute(Qt::WA_TranslucentBackground);
    blackDisksCountLabel->setFixedSize(100, 100);
    QGraphicsProxyWidget* blackDisksCountLabelProxy = new QGraphicsProxyWidget();
    blackDisksCountLabelProxy = addWidget(blackDisksCountLabel);
    blackDisksCountLabelProxy->setPos(750,  300);

    // White Disks Count Label
    whiteDisksCountLabel = new QLabel("White: " + QString::number(whiteDisksCounter));
    whiteDisksCountLabel->setAttribute(Qt::WA_TranslucentBackground);
    whiteDisksCountLabel->setFixedSize(100, 100);
    QGraphicsProxyWidget* whiteDisksCountLabelProxy = new QGraphicsProxyWidget();
    whiteDisksCountLabelProxy = addWidget(whiteDisksCountLabel);
    whiteDisksCountLabelProxy->setPos(750,  350);

    // Player Turn Label
    turnLabel = new QLabel("Black's Turn");
    turnLabel->setFixedSize(200, 100);
    turnLabel->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsProxyWidget* turnLabelProxy = new QGraphicsProxyWidget();
    turnLabelProxy = addWidget(turnLabel);
    turnLabelProxy->setPos(750,  250);

    // Placed Disk Position Label
    placedPositionLabel = new QLabel();
    placedPositionLabel->setFixedWidth(250);
    placedPositionLabel->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsProxyWidget* placedPositionLabelProxy = new QGraphicsProxyWidget();
    placedPositionLabelProxy = addWidget(placedPositionLabel);
    placedPositionLabelProxy->setPos(750,  550);

    // Initial disks
    Disk* disk = new Disk(nullptr, "white");
    disk->setPos(getScreenPosFromCoord(4), getScreenPosFromCoord(4));
    addItem(disk);
    diskMatrix[4][4] = disk;
    posMatrix[4][4] = 1;

    disk = new Disk(nullptr, "white");
    disk->setPos(getScreenPosFromCoord(5),getScreenPosFromCoord(5));
    addItem(disk);
    diskMatrix[5][5] = disk;
    posMatrix[5][5] = 1 ;

    disk = new Disk(nullptr, "black");
    disk->setPos(getScreenPosFromCoord(4), getScreenPosFromCoord(5));
    addItem(disk);
    diskMatrix[5][4] = disk;
    posMatrix[5][4] = 2 ;

    disk = new Disk(nullptr, "black");
    disk->setPos(getScreenPosFromCoord(5), getScreenPosFromCoord(4));
    addItem(disk);
    diskMatrix[4][5] = disk;
    posMatrix[4][5] = 2 ;
}

void OthelloScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF diskPosition = event->scenePos();

    // Check if click outside the game box
    if (tileSize > diskPosition.x() || diskPosition.x() > 9 * tileSize || diskPosition.y() < tileSize || diskPosition.y() > 9 * tileSize)
        return;

    qint8 i = getCoordFromScreenPos(int(diskPosition.y()));
    qint8 j = getCoordFromScreenPos(int(diskPosition.x()));

    qWarning() << "Disk Place: i: " << i << "j: " << j << "x: " << diskPosition.x() << "y: " << diskPosition.y();

    // Check if spot is empty
    if (posMatrix[i][j] != 0)
        return;

    Disk* disk = new Disk(nullptr, diskColor);
    diskPosition.setY(getScreenPosFromCoord(i));
    diskPosition.setX(getScreenPosFromCoord(j));
    disk->setPos(diskPosition);

    //Checking if the position is viable(outflanking) + flipping in case the spot is correct
    bool vertical = verticalCheckReplace(diskColor, i, j);
    bool horizontal = horizontalCheckReplace(diskColor, i, j);
    bool diagonal = diagonalCheckReplace(diskColor, i, j);
    if(!vertical && !horizontal && !diagonal)
        return;

    // Add Disk
    addItem(disk);
    diskMatrix[i][j] = disk;
    posMatrix[i][j] = getColorInt(diskColor);

    // Adjust labels
    if (diskColor == "black"){
        player1Timer->stop();
        player2Timer->start(1000);
        ++blackDisksCounter;
        diskColor = "white";
        turnLabel->setText("White's Turn");
        placedPositionLabel->setText("Black placed a disk on position " + QString(char(64 + j)) + QString::number(i));
    }
    else if (diskColor == "white"){
        player2Timer->stop();
        player1Timer->start(1000);
        ++whiteDisksCounter;
        diskColor = "black";
        turnLabel->setText("Black's Turn");
        placedPositionLabel->setText("White placed a disk on position " + QString(char(64 + j)) + QString::number(i));
    }
    blackDisksCountLabel->setText("Black: " + QString::number(blackDisksCounter));
    whiteDisksCountLabel->setText("White: " + QString::number(whiteDisksCounter));

    // Handle player who can't make any move
    if(!availableTiles()){
        if (diskColor == "black"){
            diskColor = "white";
            turnLabel->setText("Black has no moves, White's Turn");
            player1Timer->stop();
            player2Timer->start(1000);
        }
        else if (diskColor == "white"){
            diskColor = "black";
            turnLabel->setText("White has no moves, Black's Turn");
            player1Timer->stop();
            player2Timer->start(1000);
        }
        // Need call availableTiles() to show the available tiles for the new color
        // If also false then no one can place a disk ==> game Over
        if(!availableTiles())
            endGameHandler();
    }

    // End Game
    bool endGame = true;
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9 ; j++) {
            if (posMatrix[i][j] == 0)
                endGame = false;
        }
    }
    if (endGame)
        endGameHandler();

    // Printing the pos matrix for debugging
    for (int i = 1; i < 9; i++) {
        qWarning() << posMatrix[i][1] << posMatrix[i][2] << posMatrix[i][3] << posMatrix[i][4] << posMatrix[i][5] << posMatrix[i][6] <<posMatrix[i][7]<< posMatrix[i][8];
    }
    qWarning() << "\n";
    // Printing the disk matrix for debugging
//    for (int i = 1; i < 9; i++) {
//        qWarning() << diskMatrix[i][1]->diskColor << diskMatrix[i][2]->diskColor << diskMatrix[i][3]->diskColor << diskMatrix[i][4]->diskColor << diskMatrix[i][5]->diskColor << diskMatrix[i][6]->diskColor << diskMatrix[i][7]->diskColor << diskMatrix[i][8]->diskColor;
//    }
//    qWarning() << "\n";
}

bool OthelloScene::availableTiles()
{
    bool available = false;
    foreach (QGraphicsEllipseItem* ellipse, ellipseList) {
        removeItem(ellipse);
    }
    for (int i = 1; i < 9 ;i++){
        for (int j = 1; j < 9;j++ ) {
            if(posMatrix[i][j] != 0)
                continue;
            //Checking if the position is viable(outflanking)
            bool vertical = verticalCheck(diskColor, i, j);
            bool horizontal = horizontalCheck(diskColor, i, j);
            bool diagonal = diagonalCheck(diskColor, i, j);
            if(vertical || horizontal || diagonal){
                available = true;
                QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(getScreenPosFromCoord(j) + 18 , getScreenPosFromCoord(i) + 18, 10, 10);
                ellipseList.append(ellipse);
                addItem(ellipse);
            }
        }
    }
    return available;
}

bool OthelloScene::verticalCheck(QString diskColor, int i, int j){
    bool neverBounded = true;
    int intColor = getColorInt(diskColor);

    // Under the disc
    if (posMatrix[i+1][j] == getOppositeColorInt(diskColor)){
        for (int l = i + 2; l < 9; l++) {
            if (posMatrix[l][j] == intColor) {
                neverBounded = false;
                break;
            }
            else if(posMatrix[l][j] == 0)
                break;
        }
    }

    // Above the disc
    if (posMatrix[i-1][j] == getOppositeColorInt(diskColor)){
        for (int l = i - 2; l > 0; l--) {
            // Look for the next disc of the same color
            if (posMatrix[l][j] == intColor) {
                neverBounded = false;
                break;
            }
            else if(posMatrix[l][j] == 0)
                break;
        }
    }

    return !neverBounded;
}

bool OthelloScene::verticalCheckReplace(QString diskColor, int i, int j){
    bool bounded = false;
    bool neverBounded = true;
    int boundedPosition;
    int intColor = getColorInt(diskColor);

    // Above the disc
    if (posMatrix[i-1][j] == getOppositeColorInt(diskColor)){
        for (int l = i - 2; l > 0; l--) {
            // Look for the next disc of the same color
            if (posMatrix[l][j] == intColor) {
                neverBounded = false;
                bounded = true;
                boundedPosition = l;
                break;
            }
            else if(posMatrix[l][j] == 0)
                break;
        }
    }
    if(bounded){
       // If we found a bound, flip all disks in the interval found
       for (int l = i - 1; l > boundedPosition; l--) {
           flipDisk(l, j);
       }
       bounded = false;
    }

    // Under the disc
    if (posMatrix[i+1][j] == getOppositeColorInt(diskColor)){
        for (int l = i + 2; l < 9; l++) {
            if (posMatrix[l][j] == intColor) {
                neverBounded = false;
                bounded = true;
                boundedPosition = l;
                break;
            }
            else if(posMatrix[l][j] == 0)
                break;
        }
    }
    if(bounded){
        for (int l = i + 1; l < boundedPosition; l++) {
            flipDisk(l, j);
        }
        bounded = false;
    }

    // bounded is used because we can have bounds from the top and from the bottom and need to flip both
    // neverBounded is used if it is not bounded in both directions
    return !neverBounded;
}


bool OthelloScene::horizontalCheck(QString diskColor, int i, int j){
    bool neverBounded = true;
    int intColor = getColorInt(diskColor);

    // Right of the disc
    if (posMatrix[i][j+1] == getOppositeColorInt(diskColor)){
        for (int l = j + 2; l < 9; l++) {
            if (posMatrix[i][l] == intColor) {
                neverBounded = false;
                break;
            }
            else if(posMatrix[i][l] == 0)
                break;
        }
    }

    // Left of the disc
    if(posMatrix[i][j-1] == getOppositeColorInt(diskColor)){
        for (int l = j - 2; l > 0; l--) {
            if (posMatrix[i][l] == intColor) {
                neverBounded = false;
                break;
            }
            else if(posMatrix[i][l] == 0)
                break;
        }
    }

    return !neverBounded;
}


bool OthelloScene::horizontalCheckReplace(QString diskColor, int i, int j){
    bool bounded = false;
    bool neverBounded = true;
    int boundedPosition;
    int intColor = getColorInt(diskColor);

    // Left of the disc
    if(posMatrix[i][j-1] == getOppositeColorInt(diskColor)){
        for (int l = j - 2; l > 0; l--) {
            if (posMatrix[i][l] == intColor) {
                neverBounded = false;
                bounded = true;
                boundedPosition = l;
                break;
            }
            else if(posMatrix[i][l] == 0)
                break;
        }
    }
    if(bounded){
       for (int l = j - 1; l > boundedPosition; l--) {
           flipDisk(i, l);
       }
       bounded = false;
    }

    // Right of the disc
    if (posMatrix[i][j+1] == getOppositeColorInt(diskColor)){
        for (int l = j + 2; l < 9; l++) {
            if (posMatrix[i][l] == intColor) {
                neverBounded = false;
                bounded = true;
                boundedPosition = l;
                break;
            }
            else if(posMatrix[i][l] == 0)
                break;
        }
    }
    if(bounded){
        for (int l = j + 1; l < boundedPosition; l++) {
            flipDisk(i, l);
        }
        bounded = false;
    }

    return !neverBounded;
}


bool OthelloScene::diagonalCheck(QString diskColor, int i, int j){
    bool neverBounded = true;
    int intColor = getColorInt(diskColor);

    // Upper Left of the disc
    if (posMatrix[i-1][j-1] == getOppositeColorInt(diskColor)){
        for (int l = 2; i-l > 0 && j-l > 0; l++) {
            if (posMatrix[i-l][j-l] == intColor) {
                neverBounded = false;
                break;
            }
            else if(posMatrix[i-l][j-l] == 0)
                break;
        }
    }

    // Upper Right of the disc
    if( posMatrix[i-1][j+1] == getOppositeColorInt(diskColor)){
        for (int l = 2; i-l > 0 && j+l < 9; l++) {
            if (posMatrix[i-l][j+l] == intColor) {
                neverBounded = false;
                break;
            }
            else if(posMatrix[i-l][j+l] == 0)
                break;
        }
    }

    // Lower Left of the disc
    if(posMatrix[i+1][j-1] == getOppositeColorInt(diskColor)){
        for (int l = 2; i+l < 9 && j-l > 0; l++) {
            if (posMatrix[i+l][j-l] == intColor) {
                neverBounded = false;
                break;
            }
            else if(posMatrix[i+l][j-l] == 0)
                break;
        }
    }

    // Lower Right of the disc
    if(posMatrix[i+1][j+1] == getOppositeColorInt(diskColor)){
        for (int l = 2; i+l < 9 && j+l < 9; l++) {
            if (posMatrix[i+l][j+l] == intColor) {
                neverBounded = false;
                break;
            }
            else if(posMatrix[i+l][j+l] == 0)
                break;
        }
    }

    return !neverBounded;
}

bool OthelloScene::diagonalCheckReplace(QString diskColor, int i, int j){
    bool bounded = false;
    bool neverBounded = true;
    int boundedPosition;
    int intColor = getColorInt(diskColor);

    // Upper Left of the disc
    if (posMatrix[i-1][j-1] == getOppositeColorInt(diskColor)){
        for (int l = 2; i-l > 0 && j-l > 0; l++) {
            if (posMatrix[i-l][j-l] == intColor) {
                neverBounded = false;
                bounded = true;
                boundedPosition = l;
                break;
            }
            else if(posMatrix[i-l][j-l] == 0)
                break;
        }
    }
    if(bounded){
       for (int l = 1; l < boundedPosition; l++) {
           flipDisk(i-l, j-l);
       }
       bounded = false;
    }

    // Upper Right of the disc
    if( posMatrix[i-1][j+1] == getOppositeColorInt(diskColor)){
        for (int l = 2; i-l > 0 && j+l < 9; l++) {
            if (posMatrix[i-l][j+l] == intColor) {
                neverBounded = false;
                bounded = true;
                boundedPosition = l;
                break;
            }
            else if(posMatrix[i-l][j+l] == 0)
                break;
        }
    }
    if(bounded){
       for (int l = 1; l < boundedPosition; l++) {
           flipDisk(i-l, j+l);
       }
       bounded = false;
    }

    // Lower Left of the disc
    if(posMatrix[i+1][j-1] == getOppositeColorInt(diskColor)){
        for (int l = 2; i+l < 9 && j-l > 0; l++) {
            if (posMatrix[i+l][j-l] == intColor) {
                neverBounded = false;
                bounded = true;
                boundedPosition = l;
                break;
            }
            else if(posMatrix[i+l][j-l] == 0)
                break;
        }
    }
    if(bounded){
       for (int l = 1; l < boundedPosition; l++) {
           flipDisk(i+l, j-l);
       }
       bounded = false;
    }

    // Lower Right of the disc
    if(posMatrix[i+1][j+1] == getOppositeColorInt(diskColor)){
        for (int l = 2; i+l < 9 && j+l < 9; l++) {
            if (posMatrix[i+l][j+l] == intColor) {
                neverBounded = false;
                bounded = true;
                boundedPosition = l;
                break;
            }
            else if(posMatrix[i+l][j+l] == 0)
                break;
        }
    }
    if(bounded){
       for (int l = 1; l < boundedPosition; l++) {
           flipDisk(i+l, j+l);
       }
       bounded = false;
    }

    return !neverBounded;
}

void OthelloScene::endGameHandler()
{
    player1Timer->stop();
    player2Timer->stop();
    turnLabel->setFont(QFont("Times", 30));

    if (player1TimerCount > timeLimit){
        turnLabel->setText("Game Over \nWhite Wins");
        return;
    }
    else if (player2TimerCount > timeLimit){
        turnLabel->setText("Game Over \nBlack Wins");
        return;
    }

    if (blackDisksCounter > whiteDisksCounter)
        turnLabel->setText("Game Over \nBlack Wins");
    else
        turnLabel->setText("Game Over \nWhite Wins");
}

void OthelloScene::exitGame()
{
    WelcomeWidget* welcomePage = new WelcomeWidget();
    welcomePage->show();
//    delete views().first();
}

void OthelloScene::flipDisk(int i, int j)
{
    if (posMatrix[i][j] == 1){
        ++blackDisksCounter;
        --whiteDisksCounter;
        posMatrix[i][j] = 2;
    }
    else {
        --blackDisksCounter;
        ++whiteDisksCounter;
        posMatrix[i][j] = 1;
    }
    qWarning() << i << j << "Color: " << diskMatrix[i][j]->diskColor;
    diskMatrix[i][j]->flipDisk();
    qWarning() << i << j << "Color: " << diskMatrix[i][j]->diskColor;
}

int OthelloScene::getCoordFromScreenPos(int x)
{
    return x/tileSize;
}

int OthelloScene::getScreenPosFromCoord(int coord)
{
    return coord * tileSize + 20;
}

int OthelloScene::getColorInt(QString color)
{
    if (color == "white")
        return 1;
    else
        return 2;
}

int OthelloScene::getOppositeColorInt(QString color)
{
    if (color == "white")
        return 2;
    else
        return 1;
}
