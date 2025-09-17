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
    
private slots:
    void onConnected(void) {
        qInfo("Connected");
    }
    
    void onDisconnected(void) {
        qInfo("Disconnected");
    }
    
    void onErrorOccured(QAbstractSocket::SocketError) {
        qInfo("Error");
    }
    
private:
    void wire(void) {
        QObject::connect(sock, &QTcpSocket::connected, this, &TcpSocket::onConnected);
        QObject::connect(sock, &QTcpSocket::disconnected, this, &TcpSocket::onDisconnected);
        QObject::connect(sock, &QTcpSocket::errorOccurred, this, &TcpSocket::onErrorOccured);
    }

    QTcpSocket* sock;
};