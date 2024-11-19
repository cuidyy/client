#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QCryptographicHash>
#include "clientscoket.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButtonLogin_clicked();      //登录按钮

    void on_pushButtonRegister_clicked();   //注册按钮

    void on_pushButtonSelectFile_clicked(); //选择本地文件按钮

    void on_pushButtonUpload_clicked();     //上传按钮

    void on_pushButtonFlush_clicked();      //刷新按钮

private:
    QJsonObject getInput();     //获取输入值
private:
    Ui::MainWindow *ui;
    QTcpSocket *m_tcpsocket;//客户端套接字类
};
#endif // MAINWINDOW_H
