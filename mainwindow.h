#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QStringList>
#include <QFileDialog>
#include <QCryptographicHash>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QMessageBox>
#include <QSslSocket>
#include <QSslConfiguration>
#include "qaesencryption.h"
#include <map>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonRegister_clicked();
    void on_pushButtonSelectFile_clicked();
    void on_pushButtonUpload_clicked();
    void on_pushButtonFlush_clicked();
    void on_ListViewCloudDoubleClicked(const QModelIndex &index);
    void on_ListViewCloudRightClicked(const QPoint &index);

    void on_pushButtonUploadFunction_clicked();
    void on_pushButtonCloudFunction_clicked();
    void on_pushButtonLogout_clicked();
    void on_pushButtonBackFromUpload_clicked();
    void on_pushButtonBackFromCloud_clicked();
    
    // 新增的云端图片管理相关槽函数
    void on_pushButtonManageFunction_clicked();
    void on_pushButtonBackFromManage_clicked();
    void on_pushButtonDownload_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonShare_clicked();

private:
    Ui::MainWindow *ui;

    // 界面切换相关
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QWidget *functionPage;
    QWidget *uploadPage;
    QWidget *cloudPage;
    QWidget *managePage; // 新增的云端图片管理页面

    void switchToLoginPage();
    void switchToFunctionPage();
    void switchToUploadPage();
    void switchToCloudPage();
    void switchToManagePage(); // 新增的切换到云端图片管理页面的方法

    // 客户端TCP连接
    QSslSocket *m_tcpsocket;

    // 用户数据相关
    QJsonObject getInput();
    QStringList imageList;
    QString m_username;
    QString m_savePath; // 保存下载图片的路径
    std::map<std::string, bool> userLoginStatus;

    // 数据模型
    QStandardItemModel *imageModel;
    QStandardItemModel *cloudModel;
    QStandardItemModel *manageModel; // 新增的云端图片管理列表模型

    // 图片相关
    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView;
    bool isImageExists(const QString &fileName);
    void downloadThumbnail(const QString &imageName, QStandardItem *item); // 下载并生成缩略图

    // 响应消息处理
    QByteArray response;
    bool readMsg();
    void processLogin();
    void processRegister();
    void processUpload();
    void processGetlist();
    void processDownload();
    void processDelete();
    
    // 新增的云端图片管理相关处理方法
    void processManageList(); // 获取管理列表
    void processManageDownload(); // 处理下载操作
    void processManageDelete(); // 处理删除操作

    int image_count = 0;
};
#endif // MAINWINDOW_H
