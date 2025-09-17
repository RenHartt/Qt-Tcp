#pragma once

#include <QObject>
#include <QTcpSocket>

class TcpSocket : public QObject {
    Q_OBJECT
public:
    explicit TcpSocket(QObject* parent = nullptr) : QObject(parent) {
        sock = new QTcpSocket(this);
        wire();
    }
    
public slots:
    void onConnect(const QString& address, quint16 port) {
        sock->connectToHost(address, port);
    }
    
signals:
    void sendLog(const QString& log);

private slots:
    void onConnected(void) {
        emit sendLog("Connected");
    }
    
    void onDisconnected(void) {
        emit sendLog("Disconnected");
    }
    
    void onErrorOccured(QAbstractSocket::SocketError) {
        emit sendLog(sock->errorString());
    }
    
private:
    void wire(void) {
        QObject::connect(sock, &QTcpSocket::connected, this, &TcpSocket::onConnected);
        QObject::connect(sock, &QTcpSocket::disconnected, this, &TcpSocket::onDisconnected);
        QObject::connect(sock, &QTcpSocket::errorOccurred, this, &TcpSocket::onErrorOccured);
    }

    QTcpSocket* sock;
};