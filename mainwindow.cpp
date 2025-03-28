#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
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
    
    // 设置所有窗口Widget为透明，这样能看到主窗口的背景
    loginPage->setStyleSheet("QWidget#loginPage { background: transparent; }");
    functionPage->setStyleSheet("QWidget#functionPage { background: transparent; }");
    uploadPage->setStyleSheet("QWidget#uploadPage { background: transparent; }");
    cloudPage->setStyleSheet("QWidget#cloudPage { background: transparent; }");
    managePage->setStyleSheet("QWidget#managePage { background: transparent; }");
    
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
    ui->pushButtonBackFromManage->setStyleSheet(buttonStyle);
    
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

    //当双击云端列表的项时下载图片
    connect(ui->listViewCloud, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_ListViewCloudDoubleClicked(const QModelIndex &)));

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
}

// 界面切换函数
void MainWindow::switchToLoginPage()
{
    // 切换到登录界面
    stackedWidget->setCurrentWidget(loginPage);
    // 清空输入框
    ui->lineEditUserName->clear();
    ui->lineEditPassWord->clear();
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
                      "Host: 192.168.234.128:8080\r\n\r\n";

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
                      "Host: 192.168.234.128:8080\r\n\r\n";

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
                      "Host: 192.168.234.128:8080\r\n\r\n";

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
                              "Host: 192.168.234.128:8080\r\n\r\n";

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
                      "Host: 192.168.234.128:8080\r\n\r\n";

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
    //获取图片名
    QString imagename = cloudModel->data(index, Qt::DisplayRole).toString();

    // 构建HTTP GET请求报文
    QString request = "GET /download?username=" + m_username + "&imagename=" + imagename + " HTTP/1.1\r\n"
                        "Host: 192.168.234.128:8080\r\n\r\n";

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
                                                                                           "Host: 192.168.234.128:8080\r\n\r\n";

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
        for(int i = 0; i < list.size(); i++)
        {
            // 创建一个标准项用于在ListView中显示图片名称
            QStandardItem *item = new QStandardItem(list[i].toString());//获取图片名
            cloudModel->appendRow(item);
        }
    }
    if(statusCode == "500")//获取列表失败
    {
        QString msg = user["msg"].toString();
        QMessageBox::information(this, "getlist", msg);
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
        //base64解码
        QByteArray decode_data = QByteArray::fromBase64(user["imagedata"].toString().toUtf8());

        // AES128解密
        QByteArray key ("1234567812345678");
        QAESEncryption aesEnctyption(QAESEncryption::AES_128, QAESEncryption::CBC);
        QByteArray imagedata = aesEnctyption.decode(decode_data, key, key);

        //显示图片
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
            QStandardItem *item = new QStandardItem(list[i].toString());//获取图片名
            cloudModel->appendRow(item);
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
        } else {
            // 创建进度对话框
            QProgressDialog progress("正在加载缩略图...", "取消", 0, list.size(), this);
            progress.setWindowModality(Qt::WindowModal);
            progress.setMinimumDuration(500); // 只有操作超过500ms才显示进度对话框
            
            for(int i = 0; i < list.size(); i++)
            {
                progress.setValue(i);
                if (progress.wasCanceled())
                    break;
                    
                // 创建一个标准项用于在ListView中显示图片名称
                QString imageName = list[i].toString();
                QStandardItem *item = new QStandardItem(imageName);
                
                // 下载图片并生成缩略图
                downloadThumbnail(imageName, item);
                
                // 添加工具提示，方便用户查看完整文件名
                item->setToolTip(imageName);
                
                // 添加到模型
                manageModel->appendRow(item);
                
                // 处理一下其他事件，保持界面响应
                QApplication::processEvents();
            }
            
            progress.setValue(list.size());
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
    // 先设置一个默认图标，以防下载失败
    QPixmap defaultIcon(":/new/prefix1/icon.png");
    if(defaultIcon.isNull()) {
        QPixmap pixmap(24, 24);
        pixmap.fill(QColor(100, 149, 237)); // 蓝色
        item->setData(pixmap, Qt::DecorationRole);
    } else {
        item->setData(defaultIcon.scaled(24, 24), Qt::DecorationRole);
    }
    
    // 创建一个新的套接字用于下载缩略图，避免干扰主套接字
    QSslSocket *thumbnailSocket = new QSslSocket(this);
    
    // 加载并信任CA证书
    QFile certFile("C:\\Users\\administered\\Desktop\\client\\ca.crt");
    if (certFile.open(QIODevice::ReadOnly)) {
        QSslCertificate cert(&certFile, QSsl::Pem);
        QList<QSslCertificate> certs;
        certs.append(cert);

        QSslConfiguration sslConfig = thumbnailSocket->sslConfiguration();
        sslConfig.setCaCertificates(certs);
        thumbnailSocket->setSslConfiguration(sslConfig);
        certFile.close();
    }
    
    // 设置验证模式
    thumbnailSocket->setPeerVerifyMode(QSslSocket::VerifyPeer);
    
    // 连接服务器
    thumbnailSocket->connectToHostEncrypted("192.168.234.128", 8080);
    if(!thumbnailSocket->waitForEncrypted(1000)) {
        delete thumbnailSocket;
        return;
    }
    
    // 构建HTTP GET请求报文
    QString request = "GET /download?username=" + m_username + "&imagename=" + imageName + " HTTP/1.1\r\n"
                      "Host: 192.168.234.128:8080\r\n\r\n";
                      
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
    thumbnailSocket->write(msg_base64);
    
    // 等待响应
    if (!thumbnailSocket->waitForReadyRead(3000)) {
        delete thumbnailSocket;
        return;
    }
    
    // 读取响应
    QByteArray response;
    while (thumbnailSocket->bytesAvailable() || thumbnailSocket->waitForReadyRead(100)) {
        response.append(thumbnailSocket->readAll());
        
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
        break;
    }
    
    // 解析HTTP响应
    int headerEndIndex = response.indexOf("\r\n\r\n");
    if (headerEndIndex == -1) {
        delete thumbnailSocket;
        return;
    }
    
    // 获取状态行
    QByteArray statusLine = response.left(response.indexOf("\r\n"));
    
    // 获取响应体
    QByteArray jsonBody = response.mid(headerEndIndex + 4);
    
    // 将状态行的各个部分存储到列表中
    QStringList parts = QString::fromUtf8(statusLine).split(" ");
    
    // 提取状态码
    if (parts.size() < 2) {
        delete thumbnailSocket;
        return;
    }
    
    QString statusCode = parts.at(1);
    
    if (statusCode == "200") {
        // 将响应体转换为json对象
        QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
        QJsonObject user = doc.object();
        
        // base64解码
        QByteArray decode_data = QByteArray::fromBase64(user["imagedata"].toString().toUtf8());
        
        // AES128解密
        QByteArray key ("1234567812345678");
        QAESEncryption aesEnctyption(QAESEncryption::AES_128, QAESEncryption::CBC);
        QByteArray imagedata = aesEnctyption.decode(decode_data, key, key);
        
        // 加载图片
        QImage image;
        if (image.loadFromData(imagedata)) {
            // 生成缩略图并设置到列表项
            QPixmap pixmap = QPixmap::fromImage(image);
            item->setData(pixmap.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation), Qt::DecorationRole);
        }
    }
    
    // 断开连接并清理
    thumbnailSocket->disconnectFromHost();
    thumbnailSocket->deleteLater();
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
    
    // 请求下载图片
    QString request = "GET /download?username=" + m_username + "&imagename=" + imagename + " HTTP/1.1\r\n"
                      "Host: 192.168.234.128:8080\r\n\r\n";
                      
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
    
    // 保存路径，供下载完成后使用
    m_savePath = savePath;
    
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
        //base64解码
        QByteArray decode_data = QByteArray::fromBase64(user["imagedata"].toString().toUtf8());
        
        // AES128解密
        QByteArray key ("1234567812345678");
        QAESEncryption aesEnctyption(QAESEncryption::AES_128, QAESEncryption::CBC);
        QByteArray imagedata = aesEnctyption.decode(decode_data, key, key);
        
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
                      "Host: 192.168.234.128:8080\r\n\r\n";
                      
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
            
            // 添加缩略图
            QPixmap defaultIcon(":/new/prefix1/icon.png");
            if(defaultIcon.isNull()) {
                // 如果没有图标资源，创建一个简单的彩色方块作为缩略图
                QPixmap pixmap(24, 24);
                pixmap.fill(QColor(100, 149, 237)); // 蓝色
                item->setData(pixmap, Qt::DecorationRole);
            } else {
                item->setData(defaultIcon.scaled(24, 24), Qt::DecorationRole);
            }
            
            // 添加工具提示
            item->setToolTip(imageName);
            
            manageModel->appendRow(item);
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

// 分享按钮点击事件 (功能暂未实现)
void MainWindow::on_pushButtonShare_clicked()
{
    QMessageBox::information(this, "功能暂未实现", "分享功能暂未实现");
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


