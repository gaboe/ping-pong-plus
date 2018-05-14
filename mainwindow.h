#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);

    void update();
    void moveToPosition();
    bool isOnPlayerPad();
private:
    Ui::MainWindow *ui;
    int targetX;
    int targetY;
    int playerOneScore;
    int playerTwoScore;
    bool isOnPlayerSide;
    bool isPaused;
    void resetBallPosition();
    bool isOnPlayerBoundary();
    void bounceToOtherSide();
    void addScore();
    void movePlayerTwo();
    void movePlayerOne();
    void startGame();
};

#endif // MAINWINDOW_H
