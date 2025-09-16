#pragma once

#include <QObject>
#include <QTcpSocket>

class TcpSocket : public QObject {
    Q_OBJECT
public:
    explicit TcpSocket(QObject* parent = nullptr) {
        QObject::connect(&sock, &QTcpSocket::connected, this, &TcpSocket::onConnected);
        QObject::connect(&sock, &QTcpSocket::disconnected, this, &TcpSocket::onDisconnected);
        QObject::connect(&sock, &QTcpSocket::errorOccurred, this, &TcpSocket::onErrorOccured);
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
    QTcpSocket sock;
    QString ip;
    QString port;
};