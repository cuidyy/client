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
#include <QFileDialog>
#include <QStandardItemModel>
#include <iostream>
#include <fstream>
#include <map>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QSslSocket>
#include <QSslConfiguration>
#include "qaesencryption.h"
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

    void on_ListViewCloudDoubleClicked(const QModelIndex &index);//双击下载图片

    void on_ListViewCloudRightClicked(const QPoint &index);

    //void processMsg();                      //处理消息
private:
    QJsonObject getInput();     //获取输入值

    QByteArray readMsg();      //读取消息

    void processLogin();    //回复登录消息

    void processRegister(); //回复注册消息

    void processUpload();   //回复上传消息

    void processGetlist();  //处理获得图片列表消息

    void processDownload(); //处理图片下载消息

    void processDelete();   //处理图片删除消息

    bool isImageExists(const QString &fileName); //判断图片是否已在图片列表

private:
    Ui::MainWindow *ui;
    QSslSocket *m_tcpsocket;//客户端套接字类
    map<string, bool> userLoginStatus; //判断用户登录状态
    QString m_username; //用户名
    QStandardItemModel *imageModel;//QStandardItemModel 对象,用于管理要在上传列表中展示的数据
    QList<QString> imageList;//图片列表
    int image_count = 0;//记录要上传的图片数量
    QStandardItemModel *cloudModel;//管理云端列表
    QGraphicsScene *graphicsScene;//用于管理图形项,在这里用于展示图片
    QGraphicsView *graphicsView;//是用于在窗口中查看 QGraphicsScene 内容的视图类
};
#endif // MAINWINDOW_H
