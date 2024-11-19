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

    //构建 QJsonDocument对象
    QJsonDocument doc(msg);
    //将QJsonDocument对象转换为QByteArray
    QByteArray byteArray = doc.toJson();

    //base64编码消息
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //发送消息
    m_tcpsocket->write(msg_base64);

}

void MainWindow::on_pushButtonRegister_clicked()
{
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

    //构建 QJsonDocument对象
    QJsonDocument doc(msg);
    //将QJsonDocument对象转换为QByteArray
    QByteArray byteArray = doc.toJson();

    //base64编码
    QByteArray msg_base64 = byteArray.toBase64().constData();

    //发送消息
    m_tcpsocket->write(msg_base64);
}

void MainWindow::on_pushButtonSelectFile_clicked()
{}

void MainWindow::on_pushButtonUpload_clicked()
{}

void MainWindow::on_pushButtonFlush_clicked()
{}


