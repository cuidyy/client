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
#include <QTcpSocket>
#include <winsock2.h>
#include <windows.h>
#include <QObject>
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

    void processMsg();                      //处理消息
private:
    QJsonObject getInput();     //获取输入值
    QJsonObject readMsg();      //读取消息
    void processLogin(QJsonObject user); //回复登录消息
    void processRegister(QJsonObject user); //回复注册消息
private:
    Ui::MainWindow *ui;
    QTcpSocket *m_tcpsocket;//客户端套接字类
    bool is_logined = false; //登录状态
};
#endif // MAINWINDOW_H
