#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("客户端");
    setFixedSize(this->width(), this->height());

    //初始化客户端套接字
    m_tcpsocket = new QTcpSocket(this);
    //连接服务器
    m_tcpsocket->connectToHost(QHostAddress("192.168.234.128"), 8080);

    //连接断开
    connect(m_tcpsocket, &QTcpSocket::disconnected, this, [=]()
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

    //服务器消息处理
    connect(m_tcpsocket, &QTcpSocket::readyRead, this, &MainWindow::processMsg);

    //QStandardItemModel 对象,用于管理要在ListViewUpload中展示的数据
    imageModel = new QStandardItemModel(this);
    //建立了 QListView和 QStandardItemModel之间的关联，使得ListView能够从imageModel中获取数据进行展示。
    ui->listViewUpload->setModel(imageModel);

    //QStandardItemModel 对象,用于管理要在ListViewCloud中展示的数据
    cloudModel = new QStandardItemModel(this);
    ui->listViewCloud->setModel(cloudModel);

    //当双击云端列表的项时下载图片
    connect(ui->listViewCloud, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_ListViewCloudDoubleClicked(const QModelIndex &)));


    graphicsScene = new QGraphicsScene(this);
    graphicsView = new QGraphicsView(graphicsScene, this);
    //设置视图的几何尺寸
    graphicsView->setGeometry(100, 100, 500, 500);
    // 将视图设置为一个独立的窗口形式
    graphicsView->setWindowFlags(Qt::Window);

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
    //构建消息
    QJsonObject msg;
    msg.insert("user", user);
    msg.insert("request", "login");
    qDebug() << msg;

    //connect(m_tcpsocket, &QTcpSocket::readyRead, this, &MainWindow::processMsg);
    //构建 QJsonDocument对象
    QJsonDocument doc(msg);
    //将QJsonDocument对象转换为QByteArray
    QByteArray byteArray = doc.toJson();

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
    //构建消息
    QJsonObject msg;
    msg.insert("user", user);
    msg.insert("request", "register");
    qDebug() << msg;

    //connect(m_tcpsocket, &QTcpSocket::readyRead, this, &MainWindow::processMsg);
    //构建 QJsonDocument对象
    QJsonDocument doc(msg);
    //将QJsonDocument对象转换为QByteArray
    QByteArray byteArray = doc.toJson();

    //base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    //转换为网络字节序
    qDebug() << size << '\n';
    size = htonl(size);

    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

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
                // 将所选图片添加到列表
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
            QByteArray imageData = file.readAll();

            // 使用AES128加密
            QByteArray key ("1234567812345678");
            QAESEncryption aesEnctyption(QAESEncryption::AES_128, QAESEncryption::CBC);
            QByteArray encryptedData = aesEnctyption.encode(imageData, key, key);
            // 使用Base64编码
            QByteArray encodedData = encryptedData.toBase64();

            // 创建JsonObject并添加加密后的数据
            QJsonObject user;
            QJsonObject msg;
            user["username"] = m_username;
            user["imagedata"] = QString(encodedData);
            QFileInfo fileInfo(fileName);
            user["imagename"] = fileInfo.fileName();

            msg.insert("user", user);
            msg.insert("request", "upload");

            // 将JsonObject转换为字节数组
            QByteArray byteArray = QJsonDocument(msg).toJson();

            //转换为base64编码
            QByteArray msg_base64 = byteArray.toBase64().constData();

            //获取要发送数据大小
            uint32_t size = msg_base64.size();
            qDebug() << size;
            //转换为网络字节序
            size = htonl(size);
            //将size作为包头添加到发送数据前面
            msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

            // 通过TCP发送数据
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

    QJsonObject user;
    QJsonObject msg;
    user["username"] = m_username;
    msg.insert("user", user);
    msg.insert("request", "getlist");

    // 将JsonObject转换为字节数组
    QByteArray byteArray = QJsonDocument(msg).toJson();

    //转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    qDebug() << size;
    //转换为网络字节序
    size = htonl(size);
    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}

//双击图片名并下载图片
void MainWindow::on_ListViewCloudDoubleClicked(const QModelIndex &index)
{
    //获取图片名
    QString imagename = cloudModel->data(index, Qt::DisplayRole).toString();

    QJsonObject user;
    QJsonObject msg;
    user["username"] = m_username;
    user["imagename"] = imagename;
    msg.insert("user", user);
    msg.insert("request", "download");

    // 将JsonObject转换为字节数组
    QByteArray byteArray = QJsonDocument(msg).toJson();

    //转换为base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //获取要发送数据大小
    uint32_t size = msg_base64.size();
    qDebug() << size;
    //转换为网络字节序
    size = htonl(size);
    //将size作为包头添加到发送数据前面
    msg_base64.prepend(reinterpret_cast<const char*>(&size), sizeof(size));

    // 通过TCP发送数据
    m_tcpsocket->write(msg_base64);
}
//读取数据
QJsonObject MainWindow::readMsg()
{
    //读取数据包头
    while(m_tcpsocket->bytesAvailable() < 4)//数据包头不完整
    {
        QCoreApplication::processEvents();
    }

    QByteArray head = m_tcpsocket->read(4);

    uint32_t msglen;//数据长度
    memcpy(&msglen, head.data(), 4);
    msglen = ntohl(msglen);

    //读取数据
    QByteArray msg;
    while(m_tcpsocket->bytesAvailable() < msglen)//数据不完整
    {
        QCoreApplication::processEvents();
    }
    msg += m_tcpsocket->readAll();

    //base64解码
    QByteArray decode_msg = QByteArray::fromBase64(msg);

    //封装成json数据
    QJsonDocument doc = QJsonDocument::fromJson(decode_msg);
    QJsonObject json_msg = doc.object();
    qDebug() << json_msg << '\n';

    return json_msg;
}

//消息处理
void MainWindow::processMsg()
{
    QJsonObject root = readMsg();
    if(root.isEmpty())
    {
        QMessageBox::information(this, "", "数据解析为空");
    }

    //根据请求字段的值进行相应处理
    QString request = root["request"].toString();
    QJsonObject user = root;
    if(request == "login")
    {
        processLogin(user);
    }
    if(request == "register")
    {
        processRegister(user);
    }
    if(request == "upload")
    {
        processUpload(user);
    }
    if(request == "getlist")
    {
        processGetlist(user);
    }
    if(request == "download")
    {
        processDownload(user);
    }
}

//登录处理
void MainWindow::processLogin(QJsonObject user)
{
    QString msg = user["msg"].toString();
    //显示登录结果
    if(msg == "登录成功")
    {
        userLoginStatus.clear();    //删除上个用户的登录状态
        userLoginStatus[m_username.toStdString()] = true;   //更改登录状态
        cloudModel->removeRows(0,cloudModel->rowCount());   //清空云端列表
        QMessageBox::information(this, "login", msg);
    }
    else//用户不存在或密码错误
    {
        QMessageBox::information(this, "login", msg);
    }
}

//注册处理
void MainWindow::processRegister(QJsonObject user)
{
    QString msg = user["msg"].toString();
    //显示注册结果
    QMessageBox::information(this, "register", msg);
}

//处理上传
void MainWindow::processUpload(QJsonObject user)
{
    QString msg = user["msg"].toString();
    //显示上传结果
    QMessageBox::information(this, "uoload", msg);
}

//处理获得列表
void MainWindow::processGetlist(QJsonObject user)
{
    QJsonArray list = user["list"].toArray();
    for(int i = 0; i < list.size(); i++)
    {
        // 创建一个标准项用于在ListView中显示图片名称
        QStandardItem *item = new QStandardItem(list[i].toString());//获取图片名
        cloudModel->appendRow(item);
    }
}

//处理图片下载
void MainWindow::processDownload(QJsonObject user)
{
    QString msg = user["msg"].toString();
    //下载成功显示图片
    if(msg == "下载成功")
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
    else //下载失败显示下载结果
    {
        QMessageBox::information(this, "download", msg);
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


