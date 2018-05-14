#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QtDebug>
#include <QTimer>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(0));
    ui->setupUi(this);

    playerOneScore = 0;
    playerTwoScore = 0;
    ui->playerOneScore->display(playerOneScore);
    ui->playerOneScore->display(playerOneScore);

    isPaused = false;

    resetBallPosition();
    this->targetY = 400;
    QTimer::singleShot(5000, this, MainWindow::startGame);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        resetBallPosition();
        playerOneScore = 0;
        playerTwoScore = 0;
        ui->playerOneScore->display(0);
        ui->playerTwoScore->display(0);
    }

    if(event->key() == Qt::Key_P){
        isPaused = !isPaused;
        if(!isPaused){
            ui->legend1->hide();
            ui->legend2->hide();
            ui->legend3->hide();
            QTimer::singleShot(50, this, MainWindow::update);
            QTimer::singleShot(1000, this, MainWindow::movePlayerTwo);
        }
        else{
            ui->legend1->show();
            ui->legend2->show();
            ui->legend3->show();
        }
    }
}

void MainWindow::update()
{

    if(isOnPlayerBoundary() && !isOnPlayerPad()){
        addScore();
        resetBallPosition();

    }else if(isOnPlayerPad()){
        bounceToOtherSide();
    }


    MainWindow::moveToPosition();
    if(!isPaused){
        QTimer::singleShot(50, this, MainWindow::update);
    }
}

void MainWindow::movePlayerOne()
{
    QPoint globalCursorPos = QCursor::pos();
    int mouseScreen = qApp->desktop()->screenNumber(globalCursorPos);
    QRect mouseScreenGeometry = qApp->desktop()->screen(mouseScreen)->geometry();
    QPoint localCursorPos = mapFromGlobal(globalCursorPos - mouseScreenGeometry.topLeft());
    if (localCursorPos.y() > -30 && localCursorPos.y() < 520  ) {
        if(localCursorPos.y() < ui->playerOne->pos().y() && ui->playerOne->pos().y() > 20){
            ui->playerOne->move(ui->playerOne->pos().x(),ui->playerOne->pos().y() - 20);
        }

        if(localCursorPos.y() > ui->playerOne->pos().y() && ui->playerOne->pos().y() < 410){
            ui->playerOne->move(ui->playerOne->pos().x(),ui->playerOne->pos().y() + 20);
        }
    }
    QTimer::singleShot(50, this, MainWindow::movePlayerOne);

}


void MainWindow::movePlayerTwo()
{
    if(!isPaused){
        auto rise = this->targetY - ui->playerTwo->pos().y();
        auto distance = sqrt(rise * rise);
        auto velY = (rise / distance) * 1;
        if(abs(velY) >= 0.1){
            ui->playerTwo->move(ui->playerTwo->pos().x(), ui->playerTwo->pos().y() + velY);
        }
        QTimer::singleShot(50, this, MainWindow::movePlayerTwo);
    }

}

void MainWindow::startGame()
{
    ui->legend1->hide();
    ui->legend2->hide();
    ui->legend3->hide();
    QTimer::singleShot(1000, this, MainWindow::update);
    QTimer::singleShot(1000, this, MainWindow::movePlayerTwo);
    QTimer::singleShot(1000, this, MainWindow::movePlayerOne);

}

void MainWindow::addScore(){
    if(isOnPlayerSide){
        playerOneScore++;
        ui->playerTwoScore->display(playerOneScore);
    }
    else{
        playerTwoScore++;
        ui->playerOneScore->display(playerTwoScore);
    }
}

void MainWindow::bounceToOtherSide(){
    isOnPlayerSide = !isOnPlayerSide;
    targetX = isOnPlayerSide ? ui->playerOne->pos().x() + 12 : ui->playerTwo->pos().x() - 12;
    targetY = rand() % 400;
}

void MainWindow::resetBallPosition(){
    isOnPlayerSide = 0 == rand() % 2;
    targetX = isOnPlayerSide ? ui->playerOne->pos().x() + 12 : ui->playerTwo->pos().x() - 12;
    targetY = rand() % 400;
    ui->ball->move(ui->middle->pos().x(),ui->middle->pos().y());
}

bool MainWindow::isOnPlayerBoundary(){
    if(this->isOnPlayerSide){
        if(ui->ball->pos().x() - this->ui->playerOne->pos().x() < 20){
            return true;
        }
        return false;
    }
    if(this->ui->playerTwo->pos().x() - ui->ball->pos().x() < 20){
        return true;
    }
    return false;
}

bool MainWindow::isOnPlayerPad(){
    if(this->isOnPlayerSide){
        if(ui->ball->pos().x() - this->ui->playerOne->pos().x() < 20 &&
                abs(ui->ball->pos().y() - (this->ui->playerOne->pos().y() + 30)) < 55
                ){
            return true;
        }
        return false;
    }
    if(this->ui->playerTwo->pos().x() - ui->ball->pos().x()  < 20 &&
            abs(ui->ball->pos().y() - (this->ui->playerTwo->pos().y() + 30)) < 55
            ){
        return true;
    }
    return false;
}

void MainWindow::moveToPosition(){
    auto run = this->targetX - ui->ball->pos().x();
    auto rise = this->targetY - ui->ball->pos().y();
    auto distance = sqrt(run * run + rise * rise);
    auto velX = (run / distance) * 15;
    auto velY = (rise / distance) * 15;

    ui->ball->move(ui->ball->pos().x() + velX, ui->ball->pos().y() + velY);
}



