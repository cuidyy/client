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
#include <QMap>
#include <QPixmap>

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
    void on_pushButtonCancelShare_clicked();
    
    // 新增的图片共享平台相关槽函数
    void on_pushButtonShareFunction_clicked();
    void on_pushButtonFlushShare_clicked();
    void on_pushButtonCollect_clicked();
    void on_pushButtonBackFromShare_clicked();
    void on_ListViewShareDoubleClicked(const QModelIndex &index);

    // 新增的在线图片编辑相关槽函数
    void on_pushButtonEditFunction_clicked();
    void on_pushButtonBackFromEdit_clicked();
    void on_pushButtonOpenImage_clicked();
    void on_pushButtonSaveEditedImage_clicked();
    void on_pushButtonApplyFilter_clicked();
    void on_pushButtonCrop_clicked();
    void on_pushButtonRotate_clicked();
    void on_pushButtonResize_clicked();
    void on_pushButtonResetImage_clicked();

private:
    Ui::MainWindow *ui;

    // 界面切换相关
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QWidget *functionPage;
    QWidget *uploadPage;
    QWidget *cloudPage;
    QWidget *managePage; // 云端图片管理页面
    QWidget *sharePage; // 新增的共享图片平台页面
    QWidget *editPage; // 新增的在线图片编辑页面

    void switchToLoginPage();
    void switchToFunctionPage();
    void switchToUploadPage();
    void switchToCloudPage();
    void switchToManagePage();
    void switchToSharePage(); // 新增的切换到共享图片平台页面的方法
    void switchToEditPage(); // 新增的切换到在线图片编辑页面的方法

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
    QStandardItemModel *manageModel;
    QStandardItemModel *shareModel; // 新增的共享图片列表模型

    // 图片相关
    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView;
    bool isImageExists(const QString &fileName);
    void downloadThumbnail(const QString &imageName, QStandardItem *item); // 下载并生成缩略图
    void downloadShareThumbnail(const QString &imageName, const QString &username, QStandardItem *item); // 下载并生成共享图片缩略图
    QByteArray decodeImageData(const QByteArray &encodedData); // 解码图片数据

    // 响应消息处理
    QByteArray response;
    bool readMsg();
    void processLogin();
    void processRegister();
    void processUpload();
    void processGetlist();
    void processDownload();
    void processDelete();
    
    // 云端图片管理相关处理方法
    void processManageList(); // 获取管理列表
    void processManageDownload(); // 处理下载操作
    void processManageDelete(); // 处理删除操作
    void processShare(); // 处理分享操作
    void processCancelShare(); // 处理取消分享操作
    
    // 共享图片平台相关处理方法
    void processGetShare(); // 获取共享图片列表
    void processDownloadShare(); // 处理共享图片下载
    void processCollect(); // 处理收藏图片

    int image_count = 0;

    QMap<QString, QPixmap> thumbnailCache; // 添加缩略图缓存
    QMap<QString, QByteArray> imageDataCache; // 存储解码后的完整图片数据缓存
    QMap<QString, QPixmap> shareThumbCache; // 共享图片缩略图缓存
    QMap<QString, QByteArray> shareImageDataCache; // 共享图片数据缓存
    
    // 共享图片信息存储结构，用于存储图片名和用户名的关联
    struct ShareImageInfo {
        QString imageName;
        QString userName;
    };
    QList<ShareImageInfo> shareImageInfoList; // 存储共享图片信息的列表

    // 图片编辑相关
    QImage originalImage; // 原始图片
    QImage editedImage;   // 编辑后的图片
    QGraphicsScene *editScene; // 图片编辑场景
    QGraphicsPixmapItem *editPixmapItem; // 图片显示项
    
    // 编辑页面按钮
    QPushButton *m_openImageBtn;
    QPushButton *m_saveImageBtn;
    QPushButton *m_applyFilterBtn;
    QPushButton *m_cropBtn;
    QPushButton *m_rotateBtn;
    QPushButton *m_resizeBtn;
    QPushButton *m_resetImageBtn;
    QPushButton *m_backFromEditBtn;
    
    void applyFilter(const QString &filterType); // 应用滤镜
    void applyRotation(int degrees); // 应用旋转
    void applyResize(int width, int height); // 应用缩放
    void resetImageEditing(); // 重置图片编辑
};
#endif // MAINWINDOW_H
