#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maingamedisplay.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainGameDisplay = new MainGameDisplay;
    setCentralWidget(mainGameDisplay);
    mainGameDisplay->setFocus();

}

MainWindow::~MainWindow()
{
    delete ui;
}
