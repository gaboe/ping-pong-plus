#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QtDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(0));
    ui->setupUi(this);
    resetBallPosition();
    this->targetY = 400;
    QTimer::singleShot(1000, this, MainWindow::update);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Down )
    {
        ui->playerOne->move(ui->playerOne->pos().x(),ui->playerOne->pos().y() + 20);
    }

    if( event->key() == Qt::Key_Up )
    {
        ui->playerOne->move(ui->playerOne->pos().x(),ui->playerOne->pos().y() - 20);
    }
}

void MainWindow::update()
{

    if(isOnPlayerBoundary() && !isOnPlayerPad()){
        resetBallPosition();
    }else if(isOnPlayerPad()){
        bounceToOtherSide();
    }


    MainWindow::moveToPosition();
    QTimer::singleShot(50, this, MainWindow::update);
}

void MainWindow::bounceToOtherSide(){
    isOnPlayerSide = !isOnPlayerSide;
    targetX = isOnPlayerSide ? ui->playerOne->pos().x() + 12 : ui->playerTwo->pos().x() - 12;
    targetY = rand() % 150;
}

void MainWindow::resetBallPosition(){
    isOnPlayerSide = true; // 0 == rand() % 2;
    targetX = isOnPlayerSide ? ui->playerOne->pos().x() + 12 : ui->playerTwo->pos().x() - 12;
    targetY = rand() % 150;
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
            this->ui->playerTwo->pos().y() - ui->ball->pos().y() < 20
            ){
        return true;
    }
    return false;
}

void MainWindow::moveToPosition(){
    auto run = this->targetX - ui->ball->pos().x();
    auto rise = this->targetY - ui->ball->pos().y();
    auto distance = sqrt(run * run + rise * rise);
    auto velX = (run / distance) * 10;
    auto velY = (rise / distance) * 10;

    ui->ball->move(ui->ball->pos().x() + velX, ui->ball->pos().y() + velY);
}



