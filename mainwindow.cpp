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
        //exit(1);
    }

    //服务器消息处理
    connect(m_tcpsocket, &QTcpSocket::readyRead, this, &MainWindow::processMsg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

void MainWindow::on_pushButtonLogin_clicked()
{
    if(is_logined)
    {
        QMessageBox::information(this, "login", "你已登录");
        return;
    }
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

void MainWindow::on_pushButtonSelectFile_clicked()
{}

void MainWindow::on_pushButtonUpload_clicked()
{}

void MainWindow::on_pushButtonFlush_clicked()
{}

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
    qDebug() << "aaaa" << '\n';
    qDebug() << decode_msg << '\n';

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


}

//登录处理
void MainWindow::processLogin(QJsonObject user)
{
    QString msg = user["msg"].toString();
    //显示登录结果
    if(msg == "登录成功")
    {
        is_logined = true;//更改登录状态
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

