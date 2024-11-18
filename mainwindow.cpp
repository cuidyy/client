#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("客户端");
    setFixedSize(this->width(), this->height());

    //初始化套接字
    m_tcpsocket = new clientScoket(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogin_clicked()
{
    qDebug() << "aaaa";
}

void MainWindow::on_pushButtonRegister_clicked()
{
    qDebug() << "bbbb";
}

void MainWindow::on_pushButtonSelectFile_clicked()
{}

void MainWindow::on_pushButtonUpload_clicked()
{}

void MainWindow::on_pushButtonFlush_clicked()
{}
