#ifndef CLIENTSCOKET_H
#define CLIENTSCOKET_H

#include <QObject>
#include <QTcpSocket>
#include <QString>

class clientScoket : public QObject     //客户端套接字类
{
    Q_OBJECT
public:
    explicit clientScoket(QObject *parent = nullptr);

signals:
private:
    QTcpSocket *m_tcp;      //客户端套接字
    QString m_serverAddress = "127.0.0.1";      //服务器地址
    unsigned short m_port = 8080;
};

#endif // CLIENTSCOKET_H
