#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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


