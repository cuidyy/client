#include "clientscoket.h"

clientScoket::clientScoket(QObject *parent)
    : QObject{parent}
{
    m_tcp = new QTcpSocket(this);

    m_tcp->connectToHost(QHostAddress(m_serverAddress),m_port);
}
