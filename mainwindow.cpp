#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QtConcurrent/QtConcurrent>
#include <QMetaObject>
#include <QFuture>
#include <QThread>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("用户图片云存储系统");
    setFixedSize(this->width(), this->height());

    // 设置主窗口背景样式
    this->setStyleSheet("QMainWindow { background-image: url(:/new/prefix1/background.png); background-position: center; background-repeat: no-repeat; background-size: 100% 100%; }");
    
    // 设置中央部件为透明
    ui->centralwidget->setStyleSheet("QWidget { background: transparent; }");

    //初始化客户端套接字
    m_tcpsocket = new QSslSocket(this);

    // 加载并信任CA证书
    QFile certFile("C:\\Users\\administered\\Desktop\\client\\ca.crt");
    if (certFile.open(QIODevice::ReadOnly)) {
        QSslCertificate cert(&certFile, QSsl::Pem);
        QList<QSslCertificate> certs;
        certs.append(cert);

        QSslConfiguration sslConfig = m_tcpsocket->sslConfiguration();
        sslConfig.setCaCertificates(certs);
        m_tcpsocket->setSslConfiguration(sslConfig);
    } else {
        qDebug() << "Failed to load CA certificate";
    }
    
    //设置验证模式
    m_tcpsocket->setPeerVerifyMode(QSslSocket::VerifyPeer);
    //连接服务器
    if(m_tcpsocket->state() != QSslSocket::ConnectedState) {
        m_tcpsocket->connectToHostEncrypted("192.168.234.128", 8080);
        //连接超时
        if(!m_tcpsocket->waitForEncrypted(1000)) {
            QMessageBox::information(this, "", "连接服务器超时");
            exit(1);
        }
    }

    //连接断开
    connect(m_tcpsocket, &QSslSocket::disconnected, this, [=]()
    {
        QMessageBox::information(this, "", "已与服务器断开连接");
        exit(1);
    });

    //连接超时
    if(!m_tcpsocket->waitForConnected(1000))
    {
        QMessageBox::information(this, "", "连接服务器超时");
        exit(1);
    }

    // 获取stackedWidget引用和各个页面
    stackedWidget = ui->stackedWidget;
    loginPage = ui->loginPage;
    functionPage = ui->functionPage;
    uploadPage = ui->uploadPage;
    cloudPage = ui->cloudPage;
    managePage = ui->managePage;
    sharePage = ui->sharePage; // 获取共享页面引用
    
    // 设置所有窗口Widget为透明，这样能看到主窗口的背景
    loginPage->setStyleSheet("QWidget#loginPage { background: transparent; }");
    functionPage->setStyleSheet("QWidget#functionPage { background: transparent; }");
    uploadPage->setStyleSheet("QWidget#uploadPage { background: transparent; }");
    cloudPage->setStyleSheet("QWidget#cloudPage { background: transparent; }");
    managePage->setStyleSheet("QWidget#managePage { background: transparent; }");
    sharePage->setStyleSheet("QWidget#sharePage { background: transparent; }"); // 设置共享页面为透明
    
    // 设置堆叠部件为透明
    stackedWidget->setStyleSheet("QStackedWidget { background: transparent; }");
    
    // 美化按钮样式
    QString buttonStyle = "QPushButton {"
                         "border-radius: 5px;"
                         "padding: 5px;"
                         "color: white;"
                         "border: none;"
                         "background-color: rgba(50, 50, 50, 200);"
                         "}"
                         "QPushButton:hover {"
                         "background-color: rgba(70, 70, 70, 220);"
                         "}"
                         "QPushButton:pressed {"
                         "background-color: rgba(30, 30, 30, 250);"
                         "}";
    
    // 应用登录和注册按钮样式
    ui->pushButtonLogin->setStyleSheet("QPushButton {"
                                     "border-radius: 5px;"
                                     "padding: 5px;"
                                     "color: white;"
                                     "border: none;"
                                     "background-color: rgba(0, 120, 215, 220);"
                                     "}"
                                     "QPushButton:hover {"
                                     "background-color: rgba(0, 130, 230, 240);"
                                     "}"
                                     "QPushButton:pressed {"
                                     "background-color: rgba(0, 100, 200, 250);"
                                     "}");
    
    ui->pushButtonRegister->setStyleSheet("QPushButton {"
                                        "border-radius: 5px;"
                                        "padding: 5px;"
                                        "color: white;"
                                        "border: none;"
                                        "background-color: rgba(60, 160, 80, 220);"
                                        "}"
                                        "QPushButton:hover {"
                                        "background-color: rgba(70, 170, 90, 240);"
                                        "}"
                                        "QPushButton:pressed {"
                                        "background-color: rgba(50, 150, 70, 250);"
                                        "}");
    
    // 应用功能页面按钮样式
    ui->pushButtonUploadFunction->setStyleSheet(buttonStyle);
    ui->pushButtonCloudFunction->setStyleSheet(buttonStyle);
    ui->pushButtonManageFunction->setStyleSheet(buttonStyle);
    ui->pushButtonShareFunction->setStyleSheet(buttonStyle); // 添加共享图片平台按钮样式
    ui->pushButtonEditFunction->setStyleSheet(buttonStyle); // 添加在线图片编辑按钮样式
    ui->pushButtonLogout->setStyleSheet(buttonStyle);
    
    // 应用上传功能页面按钮样式
    ui->pushButtonSelectFile->setStyleSheet(buttonStyle);
    ui->pushButtonUpload->setStyleSheet(buttonStyle);
    ui->pushButtonBackFromUpload->setStyleSheet(buttonStyle);
    
    // 应用云端功能页面按钮样式
    ui->pushButtonFlush->setStyleSheet(buttonStyle);
    ui->pushButtonBackFromCloud->setStyleSheet(buttonStyle);
    
    // 应用云端管理页面按钮样式
    ui->pushButtonDownload->setStyleSheet(buttonStyle);
    ui->pushButtonDelete->setStyleSheet(buttonStyle);
    ui->pushButtonShare->setStyleSheet(buttonStyle);
    ui->pushButtonCancelShare->setStyleSheet(buttonStyle);
    ui->pushButtonBackFromManage->setStyleSheet(buttonStyle);
    
    // 应用共享平台页面按钮样式
    ui->pushButtonFlushShare->setStyleSheet(buttonStyle);
    ui->pushButtonCollect->setStyleSheet(buttonStyle);
    ui->pushButtonBackFromShare->setStyleSheet(buttonStyle);
    
    // 美化标签样式
    QString labelStyle = "QLabel {"
                        "color: white;"
                        "background-color: rgba(0, 0, 0, 100);"
                        "border-radius: 5px;"
                        "padding: 5px;"
                        "}";
    
    ui->labelTitle->setStyleSheet(labelStyle);
    ui->labelWelcome->setStyleSheet(labelStyle);
    ui->label_3->setStyleSheet(labelStyle);
    ui->label_4->setStyleSheet(labelStyle);
    ui->label_6->setStyleSheet(labelStyle);
    ui->label_7->setStyleSheet(labelStyle); // 应用相同的样式到共享图片平台标题
    
    ui->label_5->setStyleSheet("QLabel {"
                              "color: white;"
                              "background-color: rgba(0, 0, 0, 70);"
                              "border-radius: 5px;"
                              "padding: 3px;"
                              "}");
    
    // 用户名和密码标签样式
    ui->label->setStyleSheet("QLabel {"
                           "color: white;"
                           "background-color: rgba(0, 0, 0, 70);"
                           "border-radius: 5px;"
                           "padding: 3px;"
                           "}");
    
    ui->label_2->setStyleSheet("QLabel {"
                             "color: white;"
                             "background-color: rgba(0, 0, 0, 70);"
                             "border-radius: 5px;"
                             "padding: 3px;"
                             "}");
    
    // 美化输入框样式
    QString inputStyle = "QLineEdit {"
                        "background-color: rgba(255, 255, 255, 180);"
                        "border-radius: 5px;"
                        "border: 1px solid rgba(255, 255, 255, 100);"
                        "padding: 3px;"
                        "color: rgb(10, 10, 10);"
                        "}";
    
    ui->lineEditUserName->setStyleSheet(inputStyle);
    ui->lineEditPassWord->setStyleSheet(inputStyle);
    
    // 美化列表视图
    QString listViewStyle = "QListView {"
                           "background-color: rgba(255, 255, 255, 150);"
                           "border-radius: 5px;"
                           "border: 1px solid rgba(255, 255, 255, 80);"
                           "padding: 5px;"
                           "color: rgb(10, 10, 10);"
                           "}";
    ui->listViewUpload->setStyleSheet(listViewStyle);
    ui->listViewCloud->setStyleSheet(listViewStyle);
    ui->listViewManage->setStyleSheet(listViewStyle);
    ui->listViewShare->setStyleSheet(listViewStyle); // 应用相同的样式到共享图片平台列表视图
    
    // 初始界面为登录界面
    switchToLoginPage();

    //QStandardItemModel 对象,用于管理要在ListViewUpload中展示的数据
    imageModel = new QStandardItemModel(this);
    //建立了 QListView和 QStandardItemModel之间的关联，使得ListView能够从imageModel中获取数据进行展示。
    ui->listViewUpload->setModel(imageModel);

    //QStandardItemModel 对象,用于管理要在ListViewCloud中展示的数据
    cloudModel = new QStandardItemModel(this);
    ui->listViewCloud->setModel(cloudModel);

    //创建云端图片管理列表模型
    manageModel = new QStandardItemModel(this);
    ui->listViewManage->setModel(manageModel);

    //创建共享图片列表模型
    shareModel = new QStandardItemModel(this);
    ui->listViewShare->setModel(shareModel);

    //当双击云端列表的项时下载图片
    connect(ui->listViewCloud, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_ListViewCloudDoubleClicked(const QModelIndex &)));
    
    //当双击共享列表的项时下载图片
    connect(ui->listViewShare, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_ListViewShareDoubleClicked(const QModelIndex &)));

    //设置 QListView的上下文菜单策略为自定义上下文菜单模式,当设置为这种模式时，部件会在右键点击时触发 customContextMenuRequested 信号
    ui->listViewCloud->setContextMenuPolicy(Qt::CustomContextMenu);
    //右键云端列表的项时删除图片
    connect(ui->listViewCloud, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(on_ListViewCloudRightClicked(const QPoint &)));

    graphicsScene = new QGraphicsScene(this);
    graphicsView = new QGraphicsView(graphicsScene);
    //设置视图的几何尺寸
    graphicsView->setGeometry(100, 100, 500, 500);
    // 将视图设置为一个独立的窗口形式
    graphicsView->setWindowFlags(Qt::Window);

    // 在线图片编辑页面设置
    editPage = new QWidget();
    
    QVBoxLayout *editLayout = new QVBoxLayout(editPage);
    
    QLabel *editTitleLabel = new QLabel("在线图片编辑器");
    editTitleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = editTitleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    editTitleLabel->setFont(titleFont);
    
    // 创建图像编辑视图区域
    editScene = new QGraphicsScene(this);
    QGraphicsView *editView = new QGraphicsView(editScene);
    editView->setMinimumSize(400, 300);
    editView->setAlignment(Qt::AlignCenter);
    editView->setRenderHint(QPainter::Antialiasing);
    editView->setRenderHint(QPainter::SmoothPixmapTransform);
    
    // 创建图像显示项
    editPixmapItem = new QGraphicsPixmapItem();
    editScene->addItem(editPixmapItem);
    
    // 创建工具按钮区域
    QHBoxLayout *toolLayout = new QHBoxLayout();
    
    // 创建按钮实例
    QPushButton *openImageBtn = new QPushButton("打开");
    QPushButton *saveImageBtn = new QPushButton("保存");
    QPushButton *applyFilterBtn = new QPushButton("滤镜");
    QPushButton *cropBtn = new QPushButton("裁剪");
    QPushButton *rotateBtn = new QPushButton("旋转");
    QPushButton *resizeBtn = new QPushButton("调整大小");
    QPushButton *resetImageBtn = new QPushButton("重置"); 
    QPushButton *backFromEditBtn = new QPushButton("返回");
    
    // 手动连接信号和槽
    connect(openImageBtn, &QPushButton::clicked, this, &MainWindow::on_pushButtonOpenImage_clicked);
    connect(saveImageBtn, &QPushButton::clicked, this, &MainWindow::on_pushButtonSaveEditedImage_clicked);
    connect(applyFilterBtn, &QPushButton::clicked, this, &MainWindow::on_pushButtonApplyFilter_clicked);
    connect(cropBtn, &QPushButton::clicked, this, &MainWindow::on_pushButtonCrop_clicked);
    connect(rotateBtn, &QPushButton::clicked, this, &MainWindow::on_pushButtonRotate_clicked);
    connect(resizeBtn, &QPushButton::clicked, this, &MainWindow::on_pushButtonResize_clicked);
    connect(resetImageBtn, &QPushButton::clicked, this, &MainWindow::on_pushButtonResetImage_clicked); // 连接重置按钮信号
    connect(backFromEditBtn, &QPushButton::clicked, this, &MainWindow::on_pushButtonBackFromEdit_clicked);
    
    // 初始状态下，编辑按钮应该是禁用的
    applyFilterBtn->setEnabled(false);
    cropBtn->setEnabled(false);
    rotateBtn->setEnabled(false);
    resizeBtn->setEnabled(false);
    saveImageBtn->setEnabled(false);
    resetImageBtn->setEnabled(false); // 初始状态下禁用重置按钮
    
    // 保存按钮引用供后续使用
    m_openImageBtn = openImageBtn;
    m_saveImageBtn = saveImageBtn;
    m_applyFilterBtn = applyFilterBtn;
    m_cropBtn = cropBtn;
    m_rotateBtn = rotateBtn;
    m_resizeBtn = resizeBtn;
    m_resetImageBtn = resetImageBtn; // 保存重置按钮引用
    m_backFromEditBtn = backFromEditBtn;
    
    // 设置按钮样式
    QString editButtonStyle = "QPushButton {"
                             "border-radius: 5px;"
                             "padding: 8px;"
                             "color: white;"
                             "border: none;"
                             "background-color: rgba(60, 60, 60, 220);"
                             "}"
                             "QPushButton:hover {"
                             "background-color: rgba(80, 80, 80, 240);"
                             "}"
                             "QPushButton:pressed {"
                             "background-color: rgba(40, 40, 40, 250);"
                             "}"
                             "QPushButton:disabled {"
                             "background-color: rgba(120, 120, 120, 150);"
                             "color: rgba(200, 200, 200, 150);"
                             "}";
    
    openImageBtn->setStyleSheet(editButtonStyle);
    saveImageBtn->setStyleSheet(editButtonStyle);
    applyFilterBtn->setStyleSheet(editButtonStyle);
    cropBtn->setStyleSheet(editButtonStyle);
    rotateBtn->setStyleSheet(editButtonStyle);
    resizeBtn->setStyleSheet(editButtonStyle);
    resetImageBtn->setStyleSheet(editButtonStyle); // 设置重置按钮样式
    backFromEditBtn->setStyleSheet(editButtonStyle);
    
    // 添加按钮到布局
    toolLayout->addWidget(openImageBtn);
    toolLayout->addWidget(saveImageBtn);
    toolLayout->addWidget(applyFilterBtn);
    toolLayout->addWidget(cropBtn);
    toolLayout->addWidget(rotateBtn);
    toolLayout->addWidget(resizeBtn);
    toolLayout->addWidget(resetImageBtn); // 添加重置按钮到布局
    toolLayout->addWidget(backFromEditBtn);
    
    // 将所有组件添加到编辑页面布局
    editLayout->addWidget(editTitleLabel);
    editLayout->addWidget(editView);
    editLayout->addLayout(toolLayout);
    
    // 将编辑页面添加到堆栈窗口
    stackedWidget->addWidget(editPage);

    // 连接在线图片编辑按钮信号
    connect(ui->pushButtonEditFunction, SIGNAL(clicked()), this, SLOT(on_pushButtonEditFunction_clicked()));
    
    // ... existing code ...
}

// 界面切换函数
void MainWindow::switchToLoginPage()
{
    // 切换到登录界面
    stackedWidget->setCurrentWidget(loginPage);
    // 清空输入框
    ui->lineEditUserName->clear();
    ui->lineEditPassWord->clear();
    
    // 清空缩略图缓存
    thumbnailCache.clear();
    // 清空图片数据缓存
    imageDataCache.clear();
    // 清空共享图片缓存
    shareThumbCache.clear();
    shareImageDataCache.clear();
    shareImageInfoList.clear();
}

void MainWindow::switchToFunctionPage()
{
    // 切换到功能选择界面
    stackedWidget->setCurrentWidget(functionPage);
    
    // 更新欢迎文本
    QString welcomeText = "欢迎您，" + m_username;
    ui->labelWelcome->setText(welcomeText);
}

void MainWindow::switchToUploadPage()
{
    // 切换到上传功能界面
    stackedWidget->setCurrentWidget(uploadPage);
    
    // 清空上传列表
    imageModel->removeRows(0, imageModel->rowCount());
    imageList.clear();
}

void MainWindow::switchToCloudPage()
{
    // 切换到云端功能界面
    stackedWidget->setCurrentWidget(cloudPage);
    
    // 刷新云端列表
    cloudModel->removeRows(0, cloudModel->rowCount());
    on_pushButtonFlush_clicked();
}

void MainWindow::switchToManagePage()
{
    // 切换到云端图片管理界面
    stackedWidget->setCurrentWidget(managePage);
    
    // 刷新云端图片管理列表
    manageModel->removeRows(0, manageModel->rowCount());
    
    // 构建HTTP GET请求报文获取图片列表
    QString request = "GET /getlist?username=" + m_username + " HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";

    //将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();

    //转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    //转换为网络字节序
    size = htonl(size);

    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

    //服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processManageList);

    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

// 添加切换到共享图片平台页面的方法
void MainWindow::switchToSharePage()
{
    ui->stackedWidget->setCurrentWidget(ui->sharePage);
    
    // 设置固定大小的图标
    ui->listViewShare->setIconSize(QSize(120, 120));
    
    // 设置网格视图模式以在一行显示多张图片
    ui->listViewShare->setViewMode(QListView::IconMode);
    ui->listViewShare->setGridSize(QSize(150, 160)); // 调整网格大小以适应图标并留出空间
    ui->listViewShare->setResizeMode(QListView::Adjust); // 调整大小模式
    ui->listViewShare->setWrapping(true); // 启用换行
    ui->listViewShare->setSpacing(15); // 增加图片间距
    ui->listViewShare->setMovement(QListView::Static); // 禁止移动项目
    ui->listViewShare->setUniformItemSizes(true); // 使用统一的项目大小以优化布局
    ui->listViewShare->setTextElideMode(Qt::ElideRight); // 文本过长时省略
    
    // 刷新共享图片列表
    on_pushButtonFlushShare_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//获取用户名密码
QJsonObject MainWindow::getInput()
{
    QString username = ui->lineEditUserName->text();
    QString password = ui->lineEditPassWord->text();


    //封装成json格式
    QJsonObject user;
    user.insert("username", username);
    user.insert("password", password);
    return user;
}

//登录按钮
void MainWindow::on_pushButtonLogin_clicked()
{
    //获取输入内容
    QJsonObject user = getInput();

    //验证是否已登录,已登录直接返回
    QString username = user["username"].toString();
    if(userLoginStatus.find(username.toStdString()) != userLoginStatus.end() && userLoginStatus[username.toStdString()])
    {
        QMessageBox::information(this, "login", "该用户已登录");
        return;
    }
    m_username = username;//先记录下当前要登录的用户名，用于后面登录成功时更改用户登录状态信息  
    //查看账号或密码是否为空
    if(user["username"].toString().isEmpty() || user["password"].toString().isEmpty())
    {
        QMessageBox::information(this,"错误","账号或密码不能为空");
        return;
    }

    //md5加密密码
    QString pwd = user["password"].toString();
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(pwd.toUtf8());
    QByteArray pwd_md5 = hash.result().toHex();

    user["password"] = QString(pwd_md5);
    //构建请求体
    QJsonObject msg;
    msg.insert("user", user);

    //构建 QJsonDocument对象
    QJsonDocument doc(msg);
    //将QJsonDocument对象转换为QByteArray
    QByteArray requestBody = doc.toJson();

    // 构建HTTP请求报文
    QString request = "POST /login HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";

    //添加请求体
    request += requestBody;

    //将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();

    //转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    //转换为网络字节序
    size = htonl(size);

    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

    //服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processLogin);

    //发送消息
    m_tcpsocket->write(msg_base64);
}

//注册按钮
void MainWindow::on_pushButtonRegister_clicked()
{
    //获取输入内容
    QJsonObject user = getInput();
    //查看账号或密码是否为空
    if(user["username"].toString().isEmpty() || user["password"].toString().isEmpty())
    {
        QMessageBox::information(this,"错误","账号或密码不能为空");
        return;
    }

    //md5加密密码
    QString pwd = user["password"].toString();
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(pwd.toUtf8());
    QByteArray pwd_md5 = hash.result().toHex();

    user["password"] = QString(pwd_md5);
    //构建请求体
    QJsonObject msg;
    msg.insert("user", user);

    //构建 QJsonDocument对象
    QJsonDocument doc(msg);
    //将QJsonDocument对象转换为QByteArray
    QByteArray requestBody = doc.toJson();

    // 构建HTTP请求报文
    QString request = "POST /register HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";

    //添加请求体
    request += requestBody;

    //将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();

    //转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    //转换为网络字节序
    size = htonl(size);

    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

    //服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processRegister);

    //发送消息
    m_tcpsocket->write(msg_base64);
}

//选择文件按钮
void MainWindow::on_pushButtonSelectFile_clicked()
{
    //检查是否处于登录状态
    if(userLoginStatus.empty())
    {
        QMessageBox::information(this,"提示", "未登录，请登录后再进行操作。");
        return;
    }

    //选择一张或多张图片
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "选择图片", "C:\\Users\\administered\\Pictures\\Saved Pictures", "图片文件(*.png *.jpg *.jpeg)");

    if (!fileNames.isEmpty())
    {
        for(const QString &fileName : fileNames)
        {
            //检查是否已存在同名图片,同名图片直接跳过，不做二次上传
            if(!isImageExists(fileName))
            {
                // 将所 选图片添加到列表
                imageList.append(fileName);

                // 创建一个标准项用于在ListView中显示图片名称
                QStandardItem *item = new QStandardItem(fileName.split('/').last());//获取图片名

                // 加载图片并显示缩略图
                QImage image(fileName);//根据所选图片的文件名创建一个 QImage 对象，用于加载图片内容
                QPixmap pixmap = QPixmap::fromImage(image);//将 QImage 对象转换为 QPixmap 对象
                item->setData(pixmap.scaled(20, 20), Qt::DecorationRole);//设置图片的缩略图

                //由于listViewUpload与imageModel关联,在imageModel上添加item时,会自动在listViewUpload上显示
                imageModel->appendRow(item);
            }
        }
    }
}

//上传按钮
void MainWindow::on_pushButtonUpload_clicked()
{
    //检查是否处于登录状态
    if(userLoginStatus.empty())
    {
        QMessageBox::information(this,"提示", "未登录，请登录后再进行操作。");
        return;
    }

    if(imageList.isEmpty())
    {
        QMessageBox::information(this, "提示", "上传列表为空");
        return;
    }


    for(const QString &fileName : imageList)
    {
        QFile file(fileName);
        // 遍历图片列表，逐个上传
        if (file.open(QIODevice::ReadOnly))
        {
            if(image_count == 0)
            {
                //服务器消息处理
                connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processUpload);
            }
            image_count++;

            QByteArray imageData = file.readAll();

            // 使用AES128加密
            QByteArray key ("1234567812345678");
            QAESEncryption aesEnctyption(QAESEncryption::AES_128, QAESEncryption::CBC);
            QByteArray encryptedData = aesEnctyption.encode(imageData, key, key);
            // 使用Base64编码
            QByteArray encodedData = encryptedData.toBase64();

            // 创建JsonObject并添加加密后的数据
            QJsonObject user;
            user["username"] = m_username;
            user["imagedata"] = QString(encodedData);
            QFileInfo fileInfo(fileName);
            user["imagename"] = fileInfo.fileName();

            //构建请求体
            QJsonObject msg;
            msg.insert("user", user);

            //构建 QJsonDocument对象
            QJsonDocument doc(msg);
            //将QJsonDocument对象转换为QByteArray
            QByteArray requestBody = doc.toJson();

            // 构建HTTP请求报文
            QString request = "POST /upload HTTP/1.1\r\n"
                              "Host: 127.0.0.1:8080\r\n\r\n";

            //添加请求体
            request += requestBody;

            //将请求报文字符串转换为QByteArray
            QByteArray byteArray = request.toUtf8();
            //转换为base64编码
            QByteArray msg_base64 = byteArray.toBase64().constData();

            //获取要发送数据大小
            uint32_t size = msg_base64.size();
            //转换为网络字节序
            size = htonl(size);

            //将size作为包头添加到发送数据前面
            msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

            //发送消息
            m_tcpsocket->write(msg_base64);
            file.close();
        }
    }
    //清空上传列表
    imageModel->removeRows(0,imageModel->rowCount());
    //清空图片列表
    imageList.clear();

}

//刷新按钮
void MainWindow::on_pushButtonFlush_clicked()
{
    //检查是否处于登录状态
    if(userLoginStatus.empty())
    {
        QMessageBox::information(this,"提示", "未登录，请登录后再进行操作。");
        return;
    }
    //清空云端列表
    cloudModel->removeRows(0,cloudModel->rowCount());

    // 构建HTTP GET请求报文
    QString request = "GET /getlist?username=" + m_username + " HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";

    //将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();

    //转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    //转换为网络字节序
    size = htonl(size);

    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

    //服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processGetlist);

    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

//双击图片名并下载图片
void MainWindow::on_ListViewCloudDoubleClicked(const QModelIndex &index)
{
    // 获取图片名
    QString imagename = cloudModel->data(index, Qt::DisplayRole).toString();
    
    // 先检查缓存中是否有此图片数据
    if (imageDataCache.contains(imagename)) {
        // 从缓存中获取已解码的图片数据
        QByteArray imagedata = imageDataCache[imagename];
        
        // 显示图片
        QImage image;
        if (image.loadFromData(imagedata)) {
            // 在图形场景中显示图片
            graphicsScene->clear();
            graphicsScene->addPixmap(QPixmap::fromImage(image));
            graphicsView->setSceneRect(image.rect());
            graphicsView->setWindowTitle(imagename);
            graphicsView->show();
            return; // 直接返回，不需要从服务器下载
        }
    }
    
    // 缓存中没有或加载失败，从服务器下载
    // 构建HTTP GET请求报文
    QString request = "GET /download?username=" + m_username + "&imagename=" + imagename + " HTTP/1.1\r\n"
                       "Host: 127.0.0.1:8080\r\n\r\n";

    // 将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();

    // 转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    // 获取要发送数据大小
    uint32_t size = msg_base64.size();
    // 转换为网络字节序
    size = htonl(size);

    // 将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

    // 服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processDownload);

    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

//右键图片名删除图片
void MainWindow::on_ListViewCloudRightClicked(const QPoint &index)
{
    QModelIndex m_index = ui->listViewCloud->indexAt(index);
    //获取图片名
    QString imagename = cloudModel->data(m_index, Qt::DisplayRole).toString();

    // 构建HTTP GET请求报文
    QString request = "DELETE /delete?username=" + m_username + "&imagename=" + imagename + " HTTP/1.1\r\n"
                                                                                           "Host: 127.0.0.1:8080\r\n\r\n";

    //将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();

    //转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    //转换为网络字节序
    size = htonl(size);

    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

    //服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processDelete);

    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}


//读取数据
bool MainWindow::readMsg()
{
    //读取数据包头
    while(m_tcpsocket->bytesAvailable() < 4)//数据包头不完整
    {
        return false;
    }
    QByteArray head = m_tcpsocket->peek(4);//只从缓冲区复制包头，并不读取出来，保证数据的完整

    uint32_t msglen;//数据长度
    memcpy(&msglen, head.data(), 4);
    msglen = ntohl(msglen);

    //读取数据
    QByteArray msg;
    while(m_tcpsocket->bytesAvailable() < msglen + 4)//数据不完整
    {
        return false;
    }
    //丢弃掉头部4字节数据
    QByteArray temp = m_tcpsocket->read(4);

    msg += m_tcpsocket->read(msglen);

    //base64解码
    QByteArray decode_msg = QByteArray::fromBase64(msg);

    //放入response
    response = decode_msg;
    return true;
}

//登录处理
void MainWindow::processLogin()
{
    //获取http响应消息
    if(!readMsg())//数据不完整
    {
        return;
    }
    //断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processLogin);

    int headerEndIndex = response.indexOf("\r\n\r\n");
    //获取状态行
    QByteArray statusLine = response.left(headerEndIndex);

    //获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);

    //将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");

    //提取状态码
    QString statusCode = parts.at(1);

    //将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    //具体消息
    QString msg = user["msg"].toString();

    //显示登录结果
    if(statusCode == "200")
    {
        userLoginStatus.clear();    //删除上个用户的登录状态
        userLoginStatus[m_username.toStdString()] = true;   //更改登录状态
        cloudModel->removeRows(0,cloudModel->rowCount());   //清空云端列表
        QMessageBox::information(this, "login", "登录成功");
        
        // 登录成功后切换到功能选择界面
        switchToFunctionPage();
    }
    if(statusCode == "403") //用户不存在或密码错误
    {
        QMessageBox::information(this, "login", msg);
    }
    if(statusCode == "500") //连接数据库失败
    {
        QMessageBox::information(this, "login", msg);
    }
}

//注册处理
void MainWindow::processRegister()
{
    //获取http响应消息
    if(!readMsg())//数据不完整
    {
        return;
    }

    //断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processRegister);

    int headerEndIndex = response.indexOf("\r\n\r\n");
    //获取状态行
    QByteArray statusLine = response.left(headerEndIndex);

    //获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);

    //将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");

    //提取状态码
    QString statusCode = parts.at(1);

    //将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    QString msg = user["msg"].toString();
    //显示注册结果
    if(statusCode == "201") //注册成功
    {
        QMessageBox::information(this, "register", msg);
    }
    if(statusCode == "403") //用户名已存在
    {
        QMessageBox::information(this, "register", msg);
    }
    if(statusCode == "500") //数据库连接失败或插入数据库失败
    {
        QMessageBox::information(this, "register", msg);
    }
}

//处理上传
void MainWindow::processUpload()
{
    //获取http响应消息
    if(!readMsg())//数据不完整
    {
        return;
    }

    image_count--;

    int headerEndIndex = response.indexOf("\r\n\r\n");
    //获取状态行
    QByteArray statusLine = response.left(headerEndIndex);

    //获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);

    //将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");
    //提取状态码
    QString statusCode = parts.at(1);

    //将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    QString msg = user["msg"].toString();
    //显示上传结果
    if(statusCode == "200") //上传成功
    {
        QMessageBox::information(this, "uoload", msg);
    }
    if(statusCode == "500") //上传失败
    {
        QMessageBox::information(this, "uoload", msg);
    }

    if(image_count == 0)
    {
        //断开信号和槽
        disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processUpload);
    }
}

//处理获得列表
void MainWindow::processGetlist()
{
    //获取http响应消息
    if(!readMsg())//数据不完整
    {
        return;
    }

    //断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processGetlist);

    int headerEndIndex = response.indexOf("\r\n\r\n");
    //获取状态行
    QByteArray statusLine = response.left(headerEndIndex);

    //获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);

    //将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");

    //提取状态码
    QString statusCode = parts.at(1);

    //将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    if(statusCode == "200")//获取列表成功
    {
        QJsonArray list = user["list"].toArray();
        if(list.isEmpty()) {
            QMessageBox::information(this, "提示", "您的云端图片库为空");
            return;
        }

        // 先显示文件名列表
        for(int i = 0; i < list.size(); i++) {
            QString imageName = list[i].toString();
            QStandardItem *item = new QStandardItem(imageName);
            
            // 设置默认图标
            QPixmap defaultIcon(":/new/prefix1/icon.png");
            if(defaultIcon.isNull()) {
                QPixmap pixmap(48, 48);
                pixmap.fill(QColor(100, 149, 237)); // 蓝色
                item->setData(pixmap, Qt::DecorationRole);
            } else {
                item->setData(defaultIcon.scaled(48, 48), Qt::DecorationRole);
            }
            
            item->setToolTip(imageName);
            cloudModel->appendRow(item);
            
            // 先检查缓存中是否有此图片的缩略图
            if (thumbnailCache.contains(imageName)) {
                item->setData(thumbnailCache[imageName], Qt::DecorationRole);
            } else {
                // 只有在缓存中没有时，才创建线程去下载
                QFuture<void> future = QtConcurrent::run([=]() {
                    this->downloadThumbnail(imageName, item);
                });
            }
        }
    }
    else if(statusCode == "500")//获取列表失败
    {
        QString msg = user["msg"].toString();
        QMessageBox::warning(this, "获取图片列表失败", msg);
    }
}

// 下载图片并生成缩略图
void MainWindow::downloadThumbnail(const QString &imageName, QStandardItem *item)
{
    // 创建一个新的套接字用于下载缩略图
    QSslSocket thumbnailSocket;
    
    // 记录重试次数
    int retryCount = 0;
    const int maxRetries = 3;
    
    while (retryCount < maxRetries) {
        // 设置验证模式
        thumbnailSocket.setPeerVerifyMode(QSslSocket::VerifyNone);
        
        // 设置超时
        thumbnailSocket.setSocketOption(QAbstractSocket::LowDelayOption, 1);
        
        // 连接服务器
        thumbnailSocket.connectToHostEncrypted("192.168.234.128", 8080);
        if(!thumbnailSocket.waitForEncrypted(3000)) { // 增加超时时间
            qDebug() << "Connection timeout for image:" << imageName << "Error:" << thumbnailSocket.errorString();
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 构建HTTP GET请求报文
        QString request = "GET /download?username=" + m_username + "&imagename=" + imageName + " HTTP/1.1\r\n"
                        "Host: 127.0.0.1:8080\r\n\r\n";
                        
        // 将请求报文字符串转换为QByteArray
        QByteArray byteArray = request.toUtf8();
        
        // 转换为base64编码
        QByteArray msg_base64 = byteArray.toBase64();
        
        // 获取要发送数据大小
        uint32_t size = msg_base64.size();
        // 转换为网络字节序
        size = htonl(size);
        
        // 将size作为包头添加到发送数据前面
        msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));
        
        // 发送请求
        qint64 bytesWritten = thumbnailSocket.write(msg_base64);
        if (bytesWritten != msg_base64.size()) {
            qDebug() << "Failed to write all data for image:" << imageName;
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 确保所有数据已发送
        if (!thumbnailSocket.waitForBytesWritten(3000)) {
            qDebug() << "Failed to write data for image:" << imageName << "Error:" << thumbnailSocket.errorString();
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 等待响应
        if (!thumbnailSocket.waitForReadyRead(5000)) { // 增加超时时间
            qDebug() << "Response timeout for image:" << imageName << "Error:" << thumbnailSocket.errorString();
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 读取响应
        QByteArray response;
        bool readComplete = false;
        int readAttempts = 0;
        const int maxReadAttempts = 10;
        
        while (!readComplete && readAttempts < maxReadAttempts) {
            if (thumbnailSocket.bytesAvailable() > 0) {
                response.append(thumbnailSocket.readAll());
            } else if (!thumbnailSocket.waitForReadyRead(1000)) {
                readAttempts++;
                continue;
            } else {
                response.append(thumbnailSocket.readAll());
            }
            
            // 读取包头
            if (response.size() < 4) continue;
            
            uint32_t msglen;
            memcpy(&msglen, response.data(), 4);
            msglen = ntohl(msglen);
            
            // 如果数据不完整，继续读取
            if (response.size() < msglen + 4) continue;
            
            // 丢弃掉头部4字节数据
            response = response.mid(4);
            
            // base64解码
            response = QByteArray::fromBase64(response);
            readComplete = true;
            break;
        }
        
        if (!readComplete) {
            qDebug() << "Failed to read complete data for image:" << imageName;
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 解析HTTP响应
        int headerEndIndex = response.indexOf("\r\n\r\n");
        if (headerEndIndex == -1) {
            qDebug() << "Invalid HTTP response for image:" << imageName;
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 获取状态行
        QByteArray statusLine = response.left(response.indexOf("\r\n"));
        
        // 获取响应体
        QByteArray jsonBody = response.mid(headerEndIndex + 4);
        
        // 将状态行的各个部分存储到列表中
        QStringList parts = QString::fromUtf8(statusLine).split(" ");
        
        // 提取状态码
        if (parts.size() < 2) {
            qDebug() << "Invalid status line for image:" << imageName;
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        QString statusCode = parts.at(1);
        
        if (statusCode == "200") {
            // 将响应体转换为json对象
            QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
            if (doc.isNull()) {
                qDebug() << "Invalid JSON response for image:" << imageName;
                retryCount++;
                thumbnailSocket.abort();
                QThread::msleep(100 * retryCount); // 延迟一段时间后重试
                continue;
            }
            
            QJsonObject user = doc.object();
            
            // base64解码
            QByteArray decode_data = QByteArray::fromBase64(user["imagedata"].toString().toUtf8());
            if (decode_data.isEmpty()) {
                qDebug() << "Empty image data for image:" << imageName;
                retryCount++;
                thumbnailSocket.abort();
                QThread::msleep(100 * retryCount); // 延迟一段时间后重试
                continue;
            }
            
            // AES128解密
            QByteArray key ("1234567812345678");
            QAESEncryption aesEnctyption(QAESEncryption::AES_128, QAESEncryption::CBC);
            QByteArray imagedata = aesEnctyption.decode(decode_data, key, key);
            if (imagedata.isEmpty()) {
                qDebug() << "Failed to decrypt image data for image:" << imageName;
                retryCount++;
                thumbnailSocket.abort();
                QThread::msleep(100 * retryCount); // 延迟一段时间后重试
                continue;
            }
            
            // 将解码后的图片数据保存到缓存
            QMetaObject::invokeMethod(this, [this, imageName, imagedata]() {
                if (!imageDataCache.contains(imageName)) {
                    imageDataCache[imageName] = imagedata;
                }
            }, Qt::QueuedConnection);
            
            // 加载图片
            QImage image;
            if (image.loadFromData(imagedata)) {
                // 生成缩略图并设置到列表项
                QPixmap pixmap = QPixmap::fromImage(image);
                QPixmap thumbnail = pixmap.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                
                // 保存到缓存
                thumbnailCache[imageName] = thumbnail;
                
                // 使用主线程更新UI
                QMetaObject::invokeMethod(this, [this, item, thumbnail]() {
                    item->setData(thumbnail, Qt::DecorationRole);
                }, Qt::QueuedConnection);
                
                // 成功处理，退出循环
                break;
            } else {
                qDebug() << "Failed to load image data for image:" << imageName;
                retryCount++;
                thumbnailSocket.abort();
                QThread::msleep(100 * retryCount); // 延迟一段时间后重试
                continue;
            }
        } else {
            qDebug() << "HTTP error for image:" << imageName << "Status code:" << statusCode;
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
    }
    
    // 断开连接
    thumbnailSocket.disconnectFromHost();
    
    // 如果所有重试都失败，记录错误
    if (retryCount >= maxRetries) {
        qDebug() << "All retries failed for image:" << imageName;
    }
}

//处理图片下载
void MainWindow::processDownload()
{
    //获取http响应消息
    if(!readMsg())//数据不完整
    {
        return;
    }

    //断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processDownload);

    int headerEndIndex = response.indexOf("\r\n\r\n");
    //获取状态行
    QByteArray statusLine = response.left(headerEndIndex);

    //获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);

    //将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");

    //提取状态码
    QString statusCode = parts.at(1);

    //将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    QString msg = user["msg"].toString();

    //下载成功显示图片
    if(statusCode == "200")
    {
        QString imagename = user["imagename"].toString();
        
        // 获取并解码图片数据
        QByteArray encodedData = user["imagedata"].toString().toUtf8();
        QByteArray imagedata = decodeImageData(encodedData);
        
        // 将解码后的图片数据保存到缓存
        if (!imageDataCache.contains(imagename)) {
            imageDataCache[imagename] = imagedata;
        }

        // 显示图片
        QImage image;
        if (image.loadFromData(imagedata)) {
            // 在图形场景中显示图片
            graphicsScene->clear(); //清空当前 QGraphicsScene 中的所有已有图形元素
            graphicsScene->addPixmap(QPixmap::fromImage(image));    //添加图像到场景
            graphicsView->setSceneRect(image.rect());   //设置视图场景矩形 确保了视图能够准确地展示出整个图像内容

            graphicsView->setWindowTitle(imagename);//设置窗口标题
            graphicsView->show();
        } else {
            qDebug() << "无法加载图片数据";
        }
    }
    if(statusCode == "403") //图片不存在
    {
        QMessageBox::information(this, "download", msg);
    }
    if(statusCode == "500") //数据库连接失败
    {
        QMessageBox::information(this, "download", msg);
    }
}

//图片删除处理
void MainWindow::processDelete()
{
    //获取http响应消息
    if(!readMsg())//数据不完整
    {
        return;
    }

    //断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processDelete);

    int headerEndIndex = response.indexOf("\r\n\r\n");
    //获取状态行
    QByteArray statusLine = response.left(headerEndIndex);

    //获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);

    //将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");

    //提取状态码
    QString statusCode = parts.at(1);

    //将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    QString msg = user["msg"].toString();

    //删除成功返回新的图片列表
    if(statusCode == "200") //删除成功
    {
        //清空云端列表
        cloudModel->removeRows(0,cloudModel->rowCount());

        QJsonArray list = user["list"].toArray();
        for(int i = 0; i < list.size(); i++)
        {
            // 创建一个标准项用于在ListView中显示图片名称
            QString imageName = list[i].toString();
            QStandardItem *item = new QStandardItem(imageName);
            
            // 设置默认图标
            QPixmap defaultIcon(":/new/prefix1/icon.png");
            if(defaultIcon.isNull()) {
                QPixmap pixmap(48, 48);
                pixmap.fill(QColor(100, 149, 237)); // 蓝色
                item->setData(pixmap, Qt::DecorationRole);
            } else {
                item->setData(defaultIcon.scaled(48, 48), Qt::DecorationRole);
            }
            
            item->setToolTip(imageName);
            cloudModel->appendRow(item);
            
            // 先检查缓存中是否有此图片的缩略图
            if (thumbnailCache.contains(imageName)) {
                item->setData(thumbnailCache[imageName], Qt::DecorationRole);
            } else {
                // 只有在缓存中没有时，才创建线程去下载
                QFuture<void> future = QtConcurrent::run([=]() {
                    this->downloadThumbnail(imageName, item);
                });
            }
        }
    }
    if(statusCode == "500") //删除失败或数据库连接失败
    {
        QMessageBox::information(this, "delete", msg);
    }
    if(statusCode == "403") //图片不存在
    {
        QMessageBox::information(this, "delete", msg);
    }
}
bool MainWindow::isImageExists(const QString &fileName)
{
    QString baseName = QFileInfo(fileName).baseName();
    for (const QString &existingFileName : imageList)
    {
        if (QFileInfo(existingFileName).baseName() == baseName)
        {
            return true;
        }
    }
    return false;
}

// 功能选择界面按钮槽函数
void MainWindow::on_pushButtonUploadFunction_clicked()
{
    // 切换到上传功能界面
    switchToUploadPage();
}

void MainWindow::on_pushButtonCloudFunction_clicked()
{
    // 切换到云端功能界面
    switchToCloudPage();
}

void MainWindow::on_pushButtonLogout_clicked()
{
    // 退出登录
    if (!m_username.isEmpty()) {
        // 清除登录状态
        userLoginStatus.clear();
        
        // 清空缩略图缓存
        thumbnailCache.clear();
        // 清空图片数据缓存
        imageDataCache.clear();
        // 清空共享图片缓存
        shareThumbCache.clear();
        shareImageDataCache.clear();
        shareImageInfoList.clear();
        
        // 显示退出登录消息
        QMessageBox::information(this, "提示", "已退出登录");
        // 切换到登录界面
        switchToLoginPage();
    }
}

// 上传功能界面返回按钮
void MainWindow::on_pushButtonBackFromUpload_clicked()
{
    // 切换回功能选择界面
    switchToFunctionPage();
}

// 云端功能界面返回按钮
void MainWindow::on_pushButtonBackFromCloud_clicked()
{
    // 切换回功能选择界面
    switchToFunctionPage();
}

// 处理获取管理列表的响应
void MainWindow::processManageList()
{
    //获取http响应消息
    if(!readMsg())//数据不完整
    {
        return;
    }

    //断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processManageList);

    int headerEndIndex = response.indexOf("\r\n\r\n");
    //获取状态行
    QByteArray statusLine = response.left(headerEndIndex);

    //获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);

    //将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");

    //提取状态码
    QString statusCode = parts.at(1);

    //将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    if(statusCode == "200")//获取列表成功
    {
        QJsonArray list = user["list"].toArray();
        if(list.isEmpty()) {
            QMessageBox::information(this, "提示", "您的云端图片库为空");
            return;
        }
        
        // 先显示文件名列表
            for(int i = 0; i < list.size(); i++)
            {
                // 创建一个标准项用于在ListView中显示图片名称
                QString imageName = list[i].toString();
                QStandardItem *item = new QStandardItem(imageName);
                
            // 设置默认图标
            QPixmap defaultIcon(":/new/prefix1/icon.png");
            if(defaultIcon.isNull()) {
                QPixmap pixmap(48, 48);
                pixmap.fill(QColor(100, 149, 237)); // 蓝色
                item->setData(pixmap, Qt::DecorationRole);
            } else {
                item->setData(defaultIcon.scaled(48, 48), Qt::DecorationRole);
            }
            
            // 添加工具提示
                item->setToolTip(imageName);
                
                // 添加到模型
                manageModel->appendRow(item);
                
            // 先检查缓存中是否有此图片的缩略图
            if (thumbnailCache.contains(imageName)) {
                item->setData(thumbnailCache[imageName], Qt::DecorationRole);
            } else {
                // 只有在缓存中没有时，才创建线程去下载
                QFuture<void> future = QtConcurrent::run([=]() {
                    this->downloadThumbnail(imageName, item);
                });
            }
        }
    }
    else if(statusCode == "500")//获取列表失败
    {
        QString msg = user["msg"].toString();
        QMessageBox::warning(this, "获取图片列表失败", msg);
    }
}

// 下载按钮点击事件
void MainWindow::on_pushButtonDownload_clicked()
{
    //检查是否处于登录状态
    if(userLoginStatus.empty())
    {
        QMessageBox::information(this,"提示", "未登录，请登录后再进行操作。");
        return;
    }
    
    // 获取选中的图片
    QModelIndex index = ui->listViewManage->currentIndex();
    if(!index.isValid()) {
        QMessageBox::information(this, "提示", "请先选择要下载的图片");
        return;
    }
    
    // 获取图片名称
    QString imagename = manageModel->data(index, Qt::DisplayRole).toString();
    
    // 选择保存路径
    QString savePath = QFileDialog::getSaveFileName(this, "保存图片", 
                                                   QDir::homePath() + "/" + imagename, 
                                                   "图片文件(*.png *.jpg *.jpeg)");
    if(savePath.isEmpty()) {
        return; // 用户取消了保存
    }
    
    // 保存路径，供下载完成后使用
    m_savePath = savePath;
    
    // 先检查缓存中是否有此图片数据
    if (imageDataCache.contains(imagename)) {
        // 从缓存中获取已解码的图片数据
        QByteArray imagedata = imageDataCache[imagename];
        
        // 保存图片到用户选择的路径
        QFile file(m_savePath);
        if(file.open(QIODevice::WriteOnly))
        {
            file.write(imagedata);
            file.close();
            QMessageBox::information(this, "下载成功", "图片已成功保存到:\n" + m_savePath);
            return; // 直接返回，不需要从服务器下载
        }
        else
        {
            QMessageBox::critical(this, "下载失败", "无法保存图片，请检查路径权限");
            return;
        }
    }
    
    // 缓存中没有，从服务器下载
    // 请求下载图片
    QString request = "GET /download?username=" + m_username + "&imagename=" + imagename + " HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";
                      
    //将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();
    
    //转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();
    
    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    //转换为网络字节序
    size = htonl(size);
    
    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));
    
    //服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processManageDownload);
    
    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

// 处理下载响应
void MainWindow::processManageDownload()
{
    //获取http响应消息
    if(!readMsg())//数据不完整
    {
        return;
    }
    
    //断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processManageDownload);
    
    int headerEndIndex = response.indexOf("\r\n\r\n");
    //获取状态行
    QByteArray statusLine = response.left(headerEndIndex);
    
    //获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);
    
    //将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");
    
    //提取状态码
    QString statusCode = parts.at(1);
    
    //将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    QString msg = user["msg"].toString();
    
    if(statusCode == "200") // 下载成功
    {
        QString imagename = user["imagename"].toString();
        
        // 获取并解码图片数据
        QByteArray encodedData = user["imagedata"].toString().toUtf8();
        QByteArray imagedata = decodeImageData(encodedData);
        
        // 将解码后的图片数据保存到缓存
        if (!imageDataCache.contains(imagename)) {
            imageDataCache[imagename] = imagedata;
        }
        
        // 保存图片到用户选择的路径
        QFile file(m_savePath);
        if(file.open(QIODevice::WriteOnly))
        {
            file.write(imagedata);
            file.close();
            QMessageBox::information(this, "下载成功", "图片已成功保存到:\n" + m_savePath);
        }
        else
        {
            QMessageBox::critical(this, "下载失败", "无法保存图片，请检查路径权限");
        }
    }
    else if(statusCode == "403") // 图片不存在
    {
        QMessageBox::information(this, "下载", msg);
    }
    else if(statusCode == "500") // 其他错误
    {
        QMessageBox::information(this, "下载", msg);
    }
}

// 删除按钮点击事件
void MainWindow::on_pushButtonDelete_clicked()
{
    //检查是否处于登录状态
    if(userLoginStatus.empty())
    {
        QMessageBox::information(this,"提示", "未登录，请登录后再进行操作。");
        return;
    }
    
    // 获取选中的图片
    QModelIndex index = ui->listViewManage->currentIndex();
    if(!index.isValid()) {
        QMessageBox::information(this, "提示", "请先选择要删除的图片");
        return;
    }
    
    // 获取图片名称
    QString imagename = manageModel->data(index, Qt::DisplayRole).toString();
    
    // 确认删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除", "确定要删除图片 " + imagename + " 吗？",
                                  QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::No) {
        return;
    }
    
    // 发送删除请求
    QString request = "DELETE /delete?username=" + m_username + "&imagename=" + imagename + " HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";
                      
    //将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();
    
    //转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();
    
    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    //转换为网络字节序
    size = htonl(size);
    
    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));
    
    //服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processManageDelete);
    
    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

// 处理删除响应
void MainWindow::processManageDelete()
{
    //获取http响应消息
    if(!readMsg())//数据不完整
    {
        return;
    }
    
    //断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processManageDelete);
    
    int headerEndIndex = response.indexOf("\r\n\r\n");
    //获取状态行
    QByteArray statusLine = response.left(headerEndIndex);
    
    //获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);
    
    //将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");
    
    //提取状态码
    QString statusCode = parts.at(1);
    
    //将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    QString msg = user["msg"].toString();
    
    if(statusCode == "200") // 删除成功
    {
        // 清空云端管理列表
        manageModel->removeRows(0, manageModel->rowCount());
        
        // 更新列表
        QJsonArray list = user["list"].toArray();
        for(int i = 0; i < list.size(); i++)
        {
            // 创建一个标准项用于在ListView中显示图片名称
            QString imageName = list[i].toString();
            QStandardItem *item = new QStandardItem(imageName);
            
            // 添加默认缩略图
            QPixmap defaultIcon(":/new/prefix1/icon.png");
            if(defaultIcon.isNull()) {
                QPixmap pixmap(48, 48);
                pixmap.fill(QColor(100, 149, 237)); // 蓝色
                item->setData(pixmap, Qt::DecorationRole);
            } else {
                item->setData(defaultIcon.scaled(48, 48), Qt::DecorationRole);
            }
            
            // 添加工具提示
            item->setToolTip(imageName);
            
            manageModel->appendRow(item);
            
            // 先检查缓存中是否有此图片的缩略图
            if (thumbnailCache.contains(imageName)) {
                item->setData(thumbnailCache[imageName], Qt::DecorationRole);
            } else {
                // 只有在缓存中没有时，才创建线程去下载
                QFuture<void> future = QtConcurrent::run([=]() {
                    this->downloadThumbnail(imageName, item);
                });
            }
        }
        
        QMessageBox::information(this, "删除", "图片已成功删除");
    }
    else if(statusCode == "403") // 图片不存在
    {
        QMessageBox::information(this, "删除", msg);
    }
    else if(statusCode == "500") // 其他错误
    {
        QMessageBox::information(this, "删除", msg);
    }
}


// 返回按钮点击事件
void MainWindow::on_pushButtonBackFromManage_clicked()
{
    // 切换回功能选择界面
    switchToFunctionPage();
}

// 管理功能按钮点击事件
void MainWindow::on_pushButtonManageFunction_clicked()
{
    // 切换到云端图片管理界面
    switchToManagePage();
}

// 解码图片数据，将base64编码和AES加密的数据解析为原始图片数据
QByteArray MainWindow::decodeImageData(const QByteArray &encodedData)
{
    // Base64解码
    QByteArray decode_data = QByteArray::fromBase64(encodedData);
    
    // AES128解密
    QByteArray key ("1234567812345678");
    QAESEncryption aesEnctyption(QAESEncryption::AES_128, QAESEncryption::CBC);
    QByteArray imagedata = aesEnctyption.decode(decode_data, key, key);
    
    return imagedata;
}

// 新增的共享图片平台相关槽函数实现

// 共享图片平台功能按钮
void MainWindow::on_pushButtonShareFunction_clicked()
{
    // 切换到共享图片平台界面
    switchToSharePage();
}

// 刷新共享图片列表按钮
void MainWindow::on_pushButtonFlushShare_clicked()
{
    //检查是否处于登录状态
    if(userLoginStatus.empty())
    {
        QMessageBox::information(this,"提示", "未登录，请登录后再进行操作。");
        return;
    }
    //清空共享图片列表
    shareModel->removeRows(0, shareModel->rowCount());
    shareImageInfoList.clear();

    // 构建HTTP GET请求报文获取共享图片列表
    QString request = "GET /getshare HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";

    //将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();

    //转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    //转换为网络字节序
    size = htonl(size);

    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

    //服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processGetShare);

    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

// 收藏按钮点击事件 (功能暂未实现)
void MainWindow::on_pushButtonCollect_clicked()
{
    //检查是否处于登录状态
    if(userLoginStatus.empty())
    {
        QMessageBox::information(this,"提示", "未登录，请登录后再进行操作。");
        return;
    }
    
    // 获取选中的图片
    QModelIndex index = ui->listViewShare->currentIndex();
    if(!index.isValid()) {
        QMessageBox::information(this, "提示", "请先选择要收藏的图片");
        return;
    }
    
    // 获取图片信息
    int row = index.row();
    if (row < 0 || row >= shareImageInfoList.size()) {
        QMessageBox::warning(this, "提示", "图片信息无效");
        return;
    }
    
    QString imagename = shareImageInfoList[row].imageName;
    
    // 确认收藏
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认收藏", "确定要收藏图片 " + imagename + " 吗？",
                                  QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::No) {
        return;
    }
    
    // 构建JsonObject
    QJsonObject user;
    user["username"] = m_username;
    user["imagename"] = imagename;
    
    // 构建请求体
    QJsonObject msg;
    msg.insert("user", user);
    
    // 构建 QJsonDocument对象
    QJsonDocument doc(msg);
    // 将QJsonDocument对象转换为QByteArray
    QByteArray requestBody = doc.toJson();
    
    // 构建HTTP POST请求报文
    QString request = "POST /collect HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";
    
    // 添加请求体
    request += requestBody;
    
    // 将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();
    
    // 转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();
    
    // 获取要发送数据大小
    uint32_t size = msg_base64.size();
    // 转换为网络字节序
    size = htonl(size);
    
    // 将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));
    
    // 服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processCollect);
    
    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

// 处理收藏响应
void MainWindow::processCollect()
{
    // 获取http响应消息
    if(!readMsg()) { // 数据不完整
        return;
    }
    
    // 断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processCollect);
    
    int headerEndIndex = response.indexOf("\r\n\r\n");
    // 获取状态行
    QByteArray statusLine = response.left(headerEndIndex);
    
    // 获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);
    
    // 将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");
    
    // 提取状态码
    QString statusCode = parts.at(1);
    
    // 将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    QString msg = user["msg"].toString();
    QString request = user["request"].toString();
    
    if(statusCode == "200") { // 收藏成功
        QMessageBox::information(this, request, msg);
    }
    else if(statusCode == "404") { // 图片不存在
        QMessageBox::warning(this, request, msg);
    }
    else if(statusCode == "500") { // 服务器错误
        QMessageBox::critical(this, request, msg);
    }
}

// 双击共享图片下载并显示
void MainWindow::on_ListViewShareDoubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    
    // 获取图片信息
    int row = index.row();
    if (row < 0 || row >= shareImageInfoList.size()) {
        return;
    }
    
    QString imagename = shareImageInfoList[row].imageName;
    QString username = shareImageInfoList[row].userName;
    
    // 构建缓存键 (username_imagename)
    QString cacheKey = username + "_" + imagename;
    
    // 先检查缓存中是否有此图片数据
    if (shareImageDataCache.contains(cacheKey)) {
        // 从缓存中获取已解码的图片数据
        QByteArray imagedata = shareImageDataCache[cacheKey];
        
        // 显示图片
        QImage image;
        if (image.loadFromData(imagedata)) {
            // 在图形场景中显示图片
            graphicsScene->clear();
            graphicsScene->addPixmap(QPixmap::fromImage(image));
            graphicsView->setSceneRect(image.rect());
            
            // 设置窗口标题包含分享者信息
            graphicsView->setWindowTitle(username + " 分享的图片: " + imagename);
            graphicsView->show();
            return; // 直接返回，不需要从服务器下载
        }
    }
    
    // 缓存中没有或加载失败，从服务器下载
    // 构建HTTP GET请求报文
    QString request = "GET /downloadshare?username=" + username + "&imagename=" + imagename + " HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";

    // 将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();

    // 转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    // 获取要发送数据大小
    uint32_t size = msg_base64.size();
    // 转换为网络字节序
    size = htonl(size);

    // 将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

    // 服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processDownloadShare);

    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

// 处理获取共享图片列表的响应
void MainWindow::processGetShare()
{
    // 获取http响应消息
    if(!readMsg()) { // 数据不完整
        return;
    }

    // 断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processGetShare);

    int headerEndIndex = response.indexOf("\r\n\r\n");
    // 获取状态行
    QByteArray statusLine = response.left(headerEndIndex);

    // 获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);

    // 将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");

    // 提取状态码
    QString statusCode = parts.at(1);

    // 将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject jsonObj = doc.object();
    
    if(statusCode == "200") { // 获取列表成功
        QJsonArray shareList = jsonObj["list"].toArray();
        if(shareList.isEmpty()) {
            QMessageBox::information(this, "提示", "共享图片库为空");
            return;
        }

        // 清空共享图片信息列表
        shareImageInfoList.clear();

        // 先显示文件名列表
        for(int i = 0; i < shareList.size(); i++) {
            QJsonObject imageInfo = shareList[i].toObject();
            QString imageName = imageInfo["imagename"].toString();
            QString userName = imageInfo["username"].toString();
            
            // 存储图片信息
            ShareImageInfo info;
            info.imageName = imageName;
            info.userName = userName;
            shareImageInfoList.append(info);
            
            // 构建缓存键
            QString cacheKey = userName + "_" + imageName;
            
            // 创建一个标准项，不显示文本（空字符串）
            QStandardItem *item = new QStandardItem("");
            
            // 添加工具提示显示完整图片信息
            item->setToolTip(userName + " 分享的图片: " + imageName);
            
            // 设置默认图标
            QPixmap defaultIcon(":/new/prefix1/icon.png");
            if(defaultIcon.isNull()) {
                // 创建固定大小的背景
                QPixmap background(120, 120);
                background.fill(QColor(230, 230, 250)); // 淡紫色背景
                
                // 添加边框
                QPainter painter(&background);
                painter.setPen(QPen(QColor(100, 149, 237), 2)); // 蓝色边框，宽度为2
                painter.drawRect(0, 0, background.width()-1, background.height()-1);
                painter.end();
                
                item->setData(background, Qt::DecorationRole);
            } else {
                // 创建固定大小的背景
                QPixmap background(120, 120);
                background.fill(QColor(230, 230, 250)); // 淡紫色背景
                
                // 创建绘图器
                QPainter painter(&background);
                
                // 计算如何缩放图标以填充大部分区域但保留一些边距
                QPixmap scaledIcon = defaultIcon.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                
                // 在背景中央绘制图标
                int x = (background.width() - scaledIcon.width()) / 2;
                int y = (background.height() - scaledIcon.height()) / 2;
                painter.drawPixmap(x, y, scaledIcon);
                
                // 添加边框
                painter.setPen(QPen(QColor(100, 149, 237), 2)); // 蓝色边框，宽度为2
                painter.drawRect(0, 0, background.width()-1, background.height()-1);
                painter.end();
                
                item->setData(background, Qt::DecorationRole);
            }
            
            shareModel->appendRow(item);
            
            // 先检查缓存中是否有此图片的缩略图
            if (shareThumbCache.contains(cacheKey)) {
                item->setData(shareThumbCache[cacheKey], Qt::DecorationRole);
            } else {
                // 只有在缓存中没有时，才创建线程去下载
                QFuture<void> future = QtConcurrent::run([=]() {
                    this->downloadShareThumbnail(imageName, userName, item);
                });
            }
        }
    }
    else if(statusCode == "500") { // 获取列表失败
        QString msg = jsonObj["msg"].toString();
        QMessageBox::warning(this, "获取共享图片列表失败", msg);
    }
}

// 处理下载共享图片的响应
void MainWindow::processDownloadShare()
{
    // 获取http响应消息
    if(!readMsg()) { // 数据不完整
        return;
    }

    // 断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processDownloadShare);

    int headerEndIndex = response.indexOf("\r\n\r\n");
    // 获取状态行
    QByteArray statusLine = response.left(headerEndIndex);

    // 获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);

    // 将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");

    // 提取状态码
    QString statusCode = parts.at(1);

    // 将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    QString msg = user["msg"].toString();

    // 下载成功显示图片
    if(statusCode == "200") {
        QString imagename = user["imagename"].toString();
        QString username = user["username"].toString();
        
        // 构建缓存键
        QString cacheKey = username + "_" + imagename;
        
        // 获取并解码图片数据
        QByteArray encodedData = user["imagedata"].toString().toUtf8();
        QByteArray imagedata = decodeImageData(encodedData);
        
        // 将解码后的图片数据保存到缓存
        if (!shareImageDataCache.contains(cacheKey)) {
            shareImageDataCache[cacheKey] = imagedata;
        }

        // 显示图片
        QImage image;
        if (image.loadFromData(imagedata)) {
            // 在图形场景中显示图片
            graphicsScene->clear();
            graphicsScene->addPixmap(QPixmap::fromImage(image));
            graphicsView->setSceneRect(image.rect());
            graphicsView->setWindowTitle(username + " 分享的图片: " + imagename);
            graphicsView->show();
        } else {
            qDebug() << "无法加载共享图片数据";
        }
    }
    else if(statusCode == "403") { // 图片不存在
        QMessageBox::information(this, "下载共享图片", msg);
    }
    else if(statusCode == "500") { // 数据库连接失败
        QMessageBox::information(this, "下载共享图片", msg);
    }
}

//下载共享图片缩略图
void MainWindow::downloadShareThumbnail(const QString &imageName, const QString &username, QStandardItem *item)
{
    // 创建一个新的套接字用于下载缩略图
    QSslSocket thumbnailSocket;
    
    // 记录重试次数
    int retryCount = 0;
    const int maxRetries = 3;
    
    // 构建缓存键 (username_imagename)
    QString cacheKey = username + "_" + imageName;
    
    while (retryCount < maxRetries) {
        // 设置验证模式
        thumbnailSocket.setPeerVerifyMode(QSslSocket::VerifyNone);
        
        // 设置超时
        thumbnailSocket.setSocketOption(QAbstractSocket::LowDelayOption, 1);
        
        // 连接服务器
        thumbnailSocket.connectToHostEncrypted("192.168.234.128", 8080);
        if(!thumbnailSocket.waitForEncrypted(3000)) { // 增加超时时间
            qDebug() << "Connection timeout for shared image:" << imageName << "from user:" << username << "Error:" << thumbnailSocket.errorString();
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 构建HTTP GET请求报文
        QString request = "GET /downloadshare?username=" + username + "&imagename=" + imageName + " HTTP/1.1\r\n"
                        "Host: 127.0.0.1:8080\r\n\r\n";
                        
        // 将请求报文字符串转换为QByteArray
        QByteArray byteArray = request.toUtf8();
        
        // 转换为base64编码
        QByteArray msg_base64 = byteArray.toBase64();
        
        // 获取要发送数据大小
        uint32_t size = msg_base64.size();
        // 转换为网络字节序
        size = htonl(size);
        
        // 将size作为包头添加到发送数据前面
        msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));
        
        // 发送请求
        qint64 bytesWritten = thumbnailSocket.write(msg_base64);
        if (bytesWritten != msg_base64.size()) {
            qDebug() << "Failed to write all data for shared image:" << imageName << "from user:" << username;
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 确保所有数据已发送
        if (!thumbnailSocket.waitForBytesWritten(3000)) {
            qDebug() << "Failed to write data for shared image:" << imageName << "from user:" << username << "Error:" << thumbnailSocket.errorString();
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 等待响应
        if (!thumbnailSocket.waitForReadyRead(5000)) { // 增加超时时间
            qDebug() << "Response timeout for shared image:" << imageName << "from user:" << username << "Error:" << thumbnailSocket.errorString();
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 读取响应
        QByteArray response;
        bool readComplete = false;
        int readAttempts = 0;
        const int maxReadAttempts = 10;
        
        while (!readComplete && readAttempts < maxReadAttempts) {
            if (thumbnailSocket.bytesAvailable() > 0) {
                response.append(thumbnailSocket.readAll());
            } else if (!thumbnailSocket.waitForReadyRead(1000)) {
                readAttempts++;
                continue;
            } else {
                response.append(thumbnailSocket.readAll());
            }
            
            // 读取包头
            if (response.size() < 4) continue;
            
            uint32_t msglen;
            memcpy(&msglen, response.data(), 4);
            msglen = ntohl(msglen);
            
            // 如果数据不完整，继续读取
            if (response.size() < msglen + 4) continue;
            
            // 丢弃掉头部4字节数据
            response = response.mid(4);
            
            // base64解码
            response = QByteArray::fromBase64(response);
            readComplete = true;
            break;
        }
        
        if (!readComplete) {
            qDebug() << "Failed to read complete data for shared image:" << imageName << "from user:" << username;
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 解析HTTP响应
        int headerEndIndex = response.indexOf("\r\n\r\n");
        if (headerEndIndex == -1) {
            qDebug() << "Invalid HTTP response for shared image:" << imageName << "from user:" << username;
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        // 获取状态行
        QByteArray statusLine = response.left(response.indexOf("\r\n"));
        
        // 获取响应体
        QByteArray jsonBody = response.mid(headerEndIndex + 4);
        
        // 将状态行的各个部分存储到列表中
        QStringList parts = QString::fromUtf8(statusLine).split(" ");
        
        // 提取状态码
        if (parts.size() < 2) {
            qDebug() << "Invalid status line for shared image:" << imageName << "from user:" << username;
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
        
        QString statusCode = parts.at(1);
        
        if (statusCode == "200") {
            // 将响应体转换为json对象
            QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
            if (doc.isNull()) {
                qDebug() << "Invalid JSON response for shared image:" << imageName << "from user:" << username;
                retryCount++;
                thumbnailSocket.abort();
                QThread::msleep(100 * retryCount); // 延迟一段时间后重试
                continue;
            }
            
            QJsonObject user = doc.object();
            
            // base64解码
            QByteArray decode_data = QByteArray::fromBase64(user["imagedata"].toString().toUtf8());
            if (decode_data.isEmpty()) {
                qDebug() << "Empty image data for shared image:" << imageName << "from user:" << username;
                retryCount++;
                thumbnailSocket.abort();
                QThread::msleep(100 * retryCount); // 延迟一段时间后重试
                continue;
            }
            
            // AES128解密
            QByteArray key ("1234567812345678");
            QAESEncryption aesEnctyption(QAESEncryption::AES_128, QAESEncryption::CBC);
            QByteArray imagedata = aesEnctyption.decode(decode_data, key, key);
            if (imagedata.isEmpty()) {
                qDebug() << "Failed to decrypt image data for shared image:" << imageName << "from user:" << username;
                retryCount++;
                thumbnailSocket.abort();
                QThread::msleep(100 * retryCount); // 延迟一段时间后重试
                continue;
            }
            
            // 将解码后的图片数据保存到缓存
            QMetaObject::invokeMethod(this, [this, cacheKey, imagedata]() {
                if (!shareImageDataCache.contains(cacheKey)) {
                    shareImageDataCache[cacheKey] = imagedata;
                }
            }, Qt::QueuedConnection);
            
            // 加载图片
            QImage image;
            if (image.loadFromData(imagedata)) {
                // 创建固定大小的底层背景
                QPixmap background(120, 120);
                background.fill(QColor(230, 230, 250)); // 淡紫色背景
                
                // 创建绘图器
                QPainter painter(&background);
                
                // 从图像创建pixmap
                QPixmap pixmap = QPixmap::fromImage(image);
                
                // 计算如何缩放才能完全填充区域（保持比例但确保覆盖整个区域）
                QSize targetSize = background.size();
                QSize pixmapSize = pixmap.size();
                
                double widthRatio = (double)targetSize.width() / pixmapSize.width();
                double heightRatio = (double)targetSize.height() / pixmapSize.height();
                
                // 选择较大的比例确保填充整个区域
                double ratio = qMax(widthRatio, heightRatio);
                
                int newWidth = pixmapSize.width() * ratio;
                int newHeight = pixmapSize.height() * ratio;
                
                // 缩放图片以填充整个区域
                QPixmap scaledPixmap = pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                
                // 计算要裁剪的区域，确保居中
                int x = (scaledPixmap.width() - targetSize.width()) / 2;
                int y = (scaledPixmap.height() - targetSize.height()) / 2;
                
                // 裁剪过大的部分
                QPixmap croppedPixmap = scaledPixmap.copy(x, y, targetSize.width(), targetSize.height());
                
                // 在背景上绘制裁剪后的图片
                painter.drawPixmap(0, 0, croppedPixmap);
                
                // 添加边框
                painter.setPen(QPen(QColor(100, 149, 237), 2)); // 蓝色边框，宽度为2
                painter.drawRect(0, 0, targetSize.width()-1, targetSize.height()-1);
                
                painter.end();
                
                // 保存到缓存
                shareThumbCache[cacheKey] = background;
                
                // 使用主线程更新UI
                QMetaObject::invokeMethod(this, [this, item, background]() {
                    item->setData(background, Qt::DecorationRole);
                }, Qt::QueuedConnection);
                
                // 成功处理，退出循环
                break;
            } else {
                qDebug() << "Failed to load image data for shared image:" << imageName << "from user:" << username;
                retryCount++;
                thumbnailSocket.abort();
                QThread::msleep(100 * retryCount); // 延迟一段时间后重试
                continue;
            }
        } else {
            qDebug() << "HTTP error for shared image:" << imageName << "from user:" << username << "Status code:" << statusCode;
            retryCount++;
            thumbnailSocket.abort();
            QThread::msleep(100 * retryCount); // 延迟一段时间后重试
            continue;
        }
    }
    
    // 断开连接
    thumbnailSocket.disconnectFromHost();
    
    // 如果所有重试都失败，记录错误
    if (retryCount >= maxRetries) {
        qDebug() << "All retries failed for shared image:" << imageName << "from user:" << username;
    }
}

// 云端图片管理页面分享按钮点击事件
void MainWindow::on_pushButtonShare_clicked()
{
    //检查是否处于登录状态
    if(userLoginStatus.empty())
    {
        QMessageBox::information(this,"提示", "未登录，请登录后再进行操作。");
        return;
    }
    
    // 获取选中的图片
    QModelIndex index = ui->listViewManage->currentIndex();
    if(!index.isValid()) {
        QMessageBox::information(this, "提示", "请先选择要分享的图片");
        return;
    }
    
    // 获取图片名称
    QString imagename = manageModel->data(index, Qt::DisplayRole).toString();
    
    // 确认分享
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认分享", "确定要分享图片 " + imagename + " 吗？分享后其他用户可以查看该图片。",
                                  QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::No) {
        return;
    }
    
    // 构建JsonObject
    QJsonObject user;
    user["username"] = m_username;
    user["imagename"] = imagename;
    
    // 构建请求体
    QJsonObject msg;
    msg.insert("user", user);
    
    // 构建 QJsonDocument对象
    QJsonDocument doc(msg);
    // 将QJsonDocument对象转换为QByteArray
    QByteArray requestBody = doc.toJson();
    
    // 构建HTTP POST请求报文
    QString request = "POST /upshare HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";
    
    // 添加请求体
    request += requestBody;
    
    // 将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();
    
    // 转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();
    
    // 获取要发送数据大小
    uint32_t size = msg_base64.size();
    // 转换为网络字节序
    size = htonl(size);
    
    // 将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));
    
    // 服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processShare);
    
    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

// 处理分享响应
void MainWindow::processShare()
{
    // 获取http响应消息
    if(!readMsg()) { // 数据不完整
        return;
    }
    
    // 断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processShare);
    
    int headerEndIndex = response.indexOf("\r\n\r\n");
    // 获取状态行
    QByteArray statusLine = response.left(headerEndIndex);
    
    // 获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);
    
    // 将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");
    
    // 提取状态码
    QString statusCode = parts.at(1);
    
    // 将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    QString msg = user["msg"].toString();
    QString request = user["request"].toString();
    if(statusCode == "200") { // 分享成功
        QMessageBox::information(this, request, msg);
    }
    else if(statusCode == "403") { // 图片不存在或没有权限
        QMessageBox::warning(this, request, msg);
    }
    else if(statusCode == "500") { // 服务器错误
        QMessageBox::critical(this, request, msg);
    }
}

// 云端图片管理页面取消分享按钮点击事件
void MainWindow::on_pushButtonCancelShare_clicked()
{
    //检查是否处于登录状态
    if(userLoginStatus.empty())
    {
        QMessageBox::information(this,"提示", "未登录，请登录后再进行操作。");
        return;
    }
    
    // 获取选中的图片
    QModelIndex index = ui->listViewManage->currentIndex();
    if(!index.isValid()) {
        QMessageBox::information(this, "提示", "请先选择要取消分享的图片");
        return;
    }
    
    // 获取图片名称
    QString imagename = manageModel->data(index, Qt::DisplayRole).toString();
    
    // 确认取消分享
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认取消分享", "确定要取消分享图片 " + imagename + " 吗？取消后其他用户将无法查看该图片。",
                                  QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::No) {
        return;
    }
    
    // 构建JsonObject
    QJsonObject user;
    user["username"] = m_username;
    user["imagename"] = imagename;
    
    // 构建请求体
    QJsonObject msg;
    msg.insert("user", user);
    
    // 构建 QJsonDocument对象
    QJsonDocument doc(msg);
    // 将QJsonDocument对象转换为QByteArray
    QByteArray requestBody = doc.toJson();
    
    // 构建HTTP POST请求报文
    QString request = "POST /downshare HTTP/1.1\r\n"
                      "Host: 127.0.0.1:8080\r\n\r\n";
    
    // 添加请求体
    request += requestBody;
    
    // 将请求报文字符串转换为QByteArray
    QByteArray byteArray = request.toUtf8();
    
    // 转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();
    
    // 获取要发送数据大小
    uint32_t size = msg_base64.size();
    // 转换为网络字节序
    size = htonl(size);
    
    // 将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));
    
    // 服务器消息处理
    connect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processCancelShare);
    
    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

// 处理取消分享响应
void MainWindow::processCancelShare()
{
    // 获取http响应消息
    if(!readMsg()) { // 数据不完整
        return;
    }
    
    // 断开信号和槽
    disconnect(m_tcpsocket, &QSslSocket::readyRead, this, &MainWindow::processCancelShare);
    
    int headerEndIndex = response.indexOf("\r\n\r\n");
    // 获取状态行
    QByteArray statusLine = response.left(headerEndIndex);
    
    // 获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);
    
    // 将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");
    
    // 提取状态码
    QString statusCode = parts.at(1);
    
    // 将响应体转换为json对象
    QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
    QJsonObject user = doc.object();
    QString msg = user["msg"].toString();
    QString request = user["request"].toString();
    
    if(statusCode == "200") { // 取消分享成功
        QMessageBox::information(this, request, msg);
    }
    else if(statusCode == "404") { // 图片不存在或没有权限
        QMessageBox::warning(this, request, msg);
    }
    else if(statusCode == "500") { // 服务器错误
        QMessageBox::critical(this, request, msg);
    }
}

// 返回按钮点击事件
void MainWindow::on_pushButtonBackFromShare_clicked()
{
    // 切换回功能选择界面
    switchToFunctionPage();
}

// 在线图片编辑按钮点击事件
void MainWindow::on_pushButtonEditFunction_clicked()
{
    switchToEditPage();
}

// 切换到在线图片编辑页面
void MainWindow::switchToEditPage()
{
    stackedWidget->setCurrentWidget(editPage);
}

// 从编辑页面返回功能选择页面
void MainWindow::on_pushButtonBackFromEdit_clicked()
{
    // 询问用户是否保存编辑，只有在有图片被编辑的情况下
    if (!originalImage.isNull() && !editedImage.isNull()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "退出编辑", "是否保存当前编辑的图片？",
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        
        if (reply == QMessageBox::Yes) {
            // 保存编辑后的图片
            on_pushButtonSaveEditedImage_clicked();
            resetImageEditing();
            switchToFunctionPage(); // 保存后返回到功能页面
        } else if (reply == QMessageBox::Cancel) {
            // 用户取消，不做任何操作，停留在编辑页面
            return;
        } else {
            // 用户选择不保存，清空编辑状态并返回功能页面
            resetImageEditing();
            switchToFunctionPage();
        }
    } else {
        // 没有图片被编辑，直接返回功能页面
        resetImageEditing();
        switchToFunctionPage();
    }
}

// 打开图片进行编辑
void MainWindow::on_pushButtonOpenImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开图片", "", "图片文件 (*.png *.jpg *.jpeg *.bmp)");
    
    if (!fileName.isEmpty()) {
        // 加载原始图片
        originalImage.load(fileName);
        if (originalImage.isNull()) {
            QMessageBox::warning(this, "错误", "无法加载图片");
            return;
        }
        
        // 复制原始图片到编辑图片
        editedImage = originalImage;
        
        // 在图像编辑区域显示图片
        QPixmap pixmap = QPixmap::fromImage(editedImage);
        editPixmapItem->setPixmap(pixmap);
        
        // 调整场景大小以适应图片
        editScene->setSceneRect(pixmap.rect());
        
        // 更新UI状态，启用编辑按钮
        m_applyFilterBtn->setEnabled(true);
        m_cropBtn->setEnabled(true);
        m_rotateBtn->setEnabled(true);
        m_resizeBtn->setEnabled(true);
        m_saveImageBtn->setEnabled(true);
        m_resetImageBtn->setEnabled(true); // 启用重置按钮
    }
}

// 保存编辑后的图片
void MainWindow::on_pushButtonSaveEditedImage_clicked()
{
    if (editedImage.isNull()) {
        QMessageBox::warning(this, "错误", "没有可保存的图片");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", "", "PNG图片 (*.png);;JPG图片 (*.jpg);;JPEG图片 (*.jpeg);;BMP图片 (*.bmp)");
    
    if (!fileName.isEmpty()) {
        // 保存编辑后的图片
        if (editedImage.save(fileName)) {
            QMessageBox::information(this, "成功", "图片已成功保存");
        } else {
            QMessageBox::warning(this, "错误", "保存图片失败");
        }
    }
}

// 应用滤镜
void MainWindow::on_pushButtonApplyFilter_clicked()
{
    if (editedImage.isNull()) {
        QMessageBox::warning(this, "错误", "请先打开一张图片");
        return;
    }
    
    // 创建滤镜选择对话框
    QDialog dialog(this);
    dialog.setWindowTitle("选择滤镜");
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    QComboBox *comboBox = new QComboBox(&dialog);
    comboBox->addItem("灰度");
    comboBox->addItem("反色");
    comboBox->addItem("黑白");
    comboBox->addItem("锐化");
    comboBox->addItem("模糊");
    comboBox->addItem("暖色调");
    comboBox->addItem("冷色调");
    
    QPushButton *applyButton = new QPushButton("应用", &dialog);
    QPushButton *cancelButton = new QPushButton("取消", &dialog);
    
    layout->addWidget(new QLabel("选择滤镜类型:"));
    layout->addWidget(comboBox);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(applyButton);
    buttonLayout->addWidget(cancelButton);
    
    layout->addLayout(buttonLayout);
    
    connect(applyButton, &QPushButton::clicked, [&]() {
        QString filterType = comboBox->currentText();
        applyFilter(filterType);
        dialog.accept();
    });
    
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    dialog.exec();
}

// 裁剪图片
void MainWindow::on_pushButtonCrop_clicked()
{
    if (editedImage.isNull()) {
        QMessageBox::warning(this, "错误", "请先打开一张图片");
        return;
    }
    
    // 创建裁剪对话框
    QDialog dialog(this);
    dialog.setWindowTitle("裁剪图片");
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    
    QSpinBox *xSpinBox = new QSpinBox(&dialog);
    xSpinBox->setRange(0, editedImage.width() - 10);
    xSpinBox->setValue(0);
    
    QSpinBox *ySpinBox = new QSpinBox(&dialog);
    ySpinBox->setRange(0, editedImage.height() - 10);
    ySpinBox->setValue(0);
    
    QSpinBox *widthSpinBox = new QSpinBox(&dialog);
    widthSpinBox->setRange(10, editedImage.width());
    widthSpinBox->setValue(editedImage.width());
    
    QSpinBox *heightSpinBox = new QSpinBox(&dialog);
    heightSpinBox->setRange(10, editedImage.height());
    heightSpinBox->setValue(editedImage.height());
    
    // 连接宽度和X值的约束
    connect(widthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        int maxX = editedImage.width() - value;
        if (xSpinBox->value() > maxX) {
            xSpinBox->setValue(maxX);
        }
        xSpinBox->setMaximum(maxX);
    });
    
    // 连接高度和Y值的约束
    connect(heightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        int maxY = editedImage.height() - value;
        if (ySpinBox->value() > maxY) {
            ySpinBox->setValue(maxY);
        }
        ySpinBox->setMaximum(maxY);
    });
    
    QPushButton *applyButton = new QPushButton("裁剪", &dialog);
    QPushButton *cancelButton = new QPushButton("取消", &dialog);
    
    layout->addWidget(new QLabel("X坐标:"));
    layout->addWidget(xSpinBox);
    layout->addWidget(new QLabel("Y坐标:"));
    layout->addWidget(ySpinBox);
    layout->addWidget(new QLabel("宽度:"));
    layout->addWidget(widthSpinBox);
    layout->addWidget(new QLabel("高度:"));
    layout->addWidget(heightSpinBox);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(applyButton);
    buttonLayout->addWidget(cancelButton);
    
    layout->addLayout(buttonLayout);
    
    connect(applyButton, &QPushButton::clicked, [&]() {
        int x = xSpinBox->value();
        int y = ySpinBox->value();
        int width = widthSpinBox->value();
        int height = heightSpinBox->value();
        
        // 裁剪图片
        editedImage = editedImage.copy(x, y, width, height);
        
        // 更新显示
        QPixmap pixmap = QPixmap::fromImage(editedImage);
        editPixmapItem->setPixmap(pixmap);
        editScene->setSceneRect(pixmap.rect());
        
        dialog.accept();
    });
    
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    dialog.exec();
}

// 旋转图片
void MainWindow::on_pushButtonRotate_clicked()
{
    if (editedImage.isNull()) {
        QMessageBox::warning(this, "错误", "请先打开一张图片");
        return;
    }
    
    // 创建旋转对话框
    QDialog dialog(this);
    dialog.setWindowTitle("旋转图片");
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    QRadioButton *rotate90 = new QRadioButton("旋转90度", &dialog);
    QRadioButton *rotate180 = new QRadioButton("旋转180度", &dialog);
    QRadioButton *rotate270 = new QRadioButton("旋转270度", &dialog);
    QRadioButton *rotateFlipH = new QRadioButton("水平翻转", &dialog);
    QRadioButton *rotateFlipV = new QRadioButton("垂直翻转", &dialog);
    
    rotate90->setChecked(true);
    
    QPushButton *applyButton = new QPushButton("应用", &dialog);
    QPushButton *cancelButton = new QPushButton("取消", &dialog);
    
    layout->addWidget(new QLabel("选择旋转类型:"));
    layout->addWidget(rotate90);
    layout->addWidget(rotate180);
    layout->addWidget(rotate270);
    layout->addWidget(rotateFlipH);
    layout->addWidget(rotateFlipV);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(applyButton);
    buttonLayout->addWidget(cancelButton);
    
    layout->addLayout(buttonLayout);
    
    connect(applyButton, &QPushButton::clicked, [&]() {
        QImage rotatedImage;
        
        if (rotate90->isChecked()) {
            QTransform transform;
            transform.rotate(90);
            rotatedImage = editedImage.transformed(transform);
        } else if (rotate180->isChecked()) {
            QTransform transform;
            transform.rotate(180);
            rotatedImage = editedImage.transformed(transform);
        } else if (rotate270->isChecked()) {
            QTransform transform;
            transform.rotate(270);
            rotatedImage = editedImage.transformed(transform);
        } else if (rotateFlipH->isChecked()) {
            rotatedImage = editedImage.mirrored(true, false);
        } else if (rotateFlipV->isChecked()) {
            rotatedImage = editedImage.mirrored(false, true);
        }
        
        editedImage = rotatedImage;
        
        // 更新显示
        QPixmap pixmap = QPixmap::fromImage(editedImage);
        editPixmapItem->setPixmap(pixmap);
        editScene->setSceneRect(pixmap.rect());
        
        dialog.accept();
    });
    
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    dialog.exec();
}

// 调整图片大小
void MainWindow::on_pushButtonResize_clicked()
{
    if (editedImage.isNull()) {
        QMessageBox::warning(this, "错误", "请先打开一张图片");
        return;
    }
    
    // 创建调整大小对话框
    QDialog dialog(this);
    dialog.setWindowTitle("调整图片大小");
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    QSpinBox *widthSpinBox = new QSpinBox(&dialog);
    widthSpinBox->setRange(1, 3000);
    widthSpinBox->setValue(editedImage.width());
    
    QSpinBox *heightSpinBox = new QSpinBox(&dialog);
    heightSpinBox->setRange(1, 3000);
    heightSpinBox->setValue(editedImage.height());
    
    QCheckBox *keepRatioCheckBox = new QCheckBox("保持宽高比", &dialog);
    keepRatioCheckBox->setChecked(true);
    
    // 当勾选保持宽高比时，自动计算高度
    connect(keepRatioCheckBox, &QCheckBox::toggled, [=](bool checked) {
        if (checked) {
            // 重新计算高度
            double ratio = (double)editedImage.height() / editedImage.width();
            heightSpinBox->setValue(widthSpinBox->value() * ratio);
        }
    });
    
    // 当宽度变化时，如果保持宽高比，自动计算高度
    connect(widthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        if (keepRatioCheckBox->isChecked()) {
            double ratio = (double)editedImage.height() / editedImage.width();
            heightSpinBox->setValue(value * ratio);
        }
    });
    
    QPushButton *applyButton = new QPushButton("应用", &dialog);
    QPushButton *cancelButton = new QPushButton("取消", &dialog);
    
    layout->addWidget(new QLabel("宽度:"));
    layout->addWidget(widthSpinBox);
    layout->addWidget(new QLabel("高度:"));
    layout->addWidget(heightSpinBox);
    layout->addWidget(keepRatioCheckBox);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(applyButton);
    buttonLayout->addWidget(cancelButton);
    
    layout->addLayout(buttonLayout);
    
    connect(applyButton, &QPushButton::clicked, [&]() {
        int width = widthSpinBox->value();
        int height = heightSpinBox->value();
        
        // 调整图片大小
        editedImage = editedImage.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        
        // 更新显示
        QPixmap pixmap = QPixmap::fromImage(editedImage);
        editPixmapItem->setPixmap(pixmap);
        editScene->setSceneRect(pixmap.rect());
        
        dialog.accept();
    });
    
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    dialog.exec();
}

// 应用滤镜
void MainWindow::applyFilter(const QString &filterType)
{
    if (editedImage.isNull()) {
        return;
    }
    
    QImage filteredImage = editedImage;
    
    if (filterType == "灰度") {
        // 灰度滤镜
        for (int y = 0; y < filteredImage.height(); y++) {
            for (int x = 0; x < filteredImage.width(); x++) {
                QRgb pixel = filteredImage.pixel(x, y);
                int gray = qGray(pixel);
                filteredImage.setPixel(x, y, qRgb(gray, gray, gray));
            }
        }
    } else if (filterType == "反色") {
        // 反色滤镜
        filteredImage.invertPixels();
    } else if (filterType == "黑白") {
        // 黑白滤镜（二值化）
        for (int y = 0; y < filteredImage.height(); y++) {
            for (int x = 0; x < filteredImage.width(); x++) {
                QRgb pixel = filteredImage.pixel(x, y);
                int gray = qGray(pixel);
                QRgb bw = (gray > 128) ? qRgb(255, 255, 255) : qRgb(0, 0, 0);
                filteredImage.setPixel(x, y, bw);
            }
        }
    } else if (filterType == "暖色调") {
        // 暖色调滤镜（增加红色和黄色）
        for (int y = 0; y < filteredImage.height(); y++) {
            for (int x = 0; x < filteredImage.width(); x++) {
                QRgb pixel = filteredImage.pixel(x, y);
                int r = qRed(pixel);
                int g = qGreen(pixel);
                int b = qBlue(pixel);
                
                r = qMin(r + 30, 255);
                g = qMin(g + 15, 255);
                
                filteredImage.setPixel(x, y, qRgb(r, g, b));
            }
        }
    } else if (filterType == "冷色调") {
        // 冷色调滤镜（增加蓝色）
        for (int y = 0; y < filteredImage.height(); y++) {
            for (int x = 0; x < filteredImage.width(); x++) {
                QRgb pixel = filteredImage.pixel(x, y);
                int r = qRed(pixel);
                int g = qGreen(pixel);
                int b = qBlue(pixel);
                
                b = qMin(b + 30, 255);
                r = qMax(r - 10, 0);
                
                filteredImage.setPixel(x, y, qRgb(r, g, b));
            }
        }
    } else if (filterType == "锐化" || filterType == "模糊") {
        // 锐化和模糊滤镜需要使用卷积
        QImage tempImage = filteredImage.convertToFormat(QImage::Format_RGB32);
        
        // 创建卷积核
        QVector<QVector<float>> kernel;
        if (filterType == "锐化") {
            // 锐化卷积核
            kernel = {
                {0, -1, 0},
                {-1, 5, -1},
                {0, -1, 0}
            };
        } else {
            // 模糊卷积核 (平均模糊)
            kernel = {
                {1.0/9, 1.0/9, 1.0/9},
                {1.0/9, 1.0/9, 1.0/9},
                {1.0/9, 1.0/9, 1.0/9}
            };
        }
        
        // 应用卷积
        int kernelSize = kernel.size();
        int kernelRadius = kernelSize / 2;
        
        for (int y = kernelRadius; y < tempImage.height() - kernelRadius; y++) {
            for (int x = kernelRadius; x < tempImage.width() - kernelRadius; x++) {
                float sumR = 0, sumG = 0, sumB = 0;
                
                for (int ky = -kernelRadius; ky <= kernelRadius; ky++) {
                    for (int kx = -kernelRadius; kx <= kernelRadius; kx++) {
                        QRgb pixel = tempImage.pixel(x + kx, y + ky);
                        float kernelValue = kernel[ky + kernelRadius][kx + kernelRadius];
                        
                        sumR += qRed(pixel) * kernelValue;
                        sumG += qGreen(pixel) * kernelValue;
                        sumB += qBlue(pixel) * kernelValue;
                    }
                }
                
                // 确保值在0-255范围内
                int r = qBound(0, int(sumR), 255);
                int g = qBound(0, int(sumG), 255);
                int b = qBound(0, int(sumB), 255);
                
                filteredImage.setPixel(x, y, qRgb(r, g, b));
            }
        }
    }
    
    editedImage = filteredImage;
    
    // 更新显示
    QPixmap pixmap = QPixmap::fromImage(editedImage);
    editPixmapItem->setPixmap(pixmap);
}

// 重置图片编辑
void MainWindow::resetImageEditing()
{
    originalImage = QImage();
    editedImage = QImage();
    
    // 清空图像显示，但不删除项目
    editPixmapItem->setPixmap(QPixmap());
    
    // 注意：不要在设置空图片后调用clear()，这会删除editPixmapItem
    // 如果之前调用了clear()，需要确保重新添加项目
    if (!editScene->items().contains(editPixmapItem)) {
        editScene->addItem(editPixmapItem);
    }
    
    // 重置场景大小
    editScene->setSceneRect(QRectF());
    
    // 禁用编辑按钮
    m_applyFilterBtn->setEnabled(false);
    m_cropBtn->setEnabled(false);
    m_rotateBtn->setEnabled(false);
    m_resizeBtn->setEnabled(false);
    m_saveImageBtn->setEnabled(false);
    m_resetImageBtn->setEnabled(false); // 禁用重置按钮
}

// 重置图片到原始状态
void MainWindow::on_pushButtonResetImage_clicked()
{
    if (originalImage.isNull()) {
        QMessageBox::warning(this, "错误", "没有可重置的图片");
        return;
    }
    
    // 询问用户是否确定重置
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "重置", "确定要恢复到原始图片吗？",
                                 QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // 将编辑图片重置为原始图片
        editedImage = originalImage;
        
        // 更新显示
        QPixmap pixmap = QPixmap::fromImage(editedImage);
        editPixmapItem->setPixmap(pixmap);
        editScene->setSceneRect(pixmap.rect());
        
        QMessageBox::information(this, "成功", "图片已重置");
    }
}


