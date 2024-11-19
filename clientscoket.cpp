#include "clientscoket.h"

clientScoket::clientScoket(QObject *parent)
    : QObject{parent}
{
    m_tcp = new QTcpSocket(this);
    //  连接服务器
    m_tcp->connectToHost(QHostAddress(m_serverAddress),m_port);


}
