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
    void connectToHost(const QString& address, quint16 port) {
        sock->connectToHost(address, port);
    }

    void disconnectFromHost(void) {
        sock->disconnectFromHost();
    }

    void onSend(const QByteArray& data) {
        sock->write(data);
        emit messageSent(data);
    }

    void readyRead(void) {
        emit messageReceived(sock->readLine());
    }
    
signals:
    void messageReceived(const QByteArray& message);
    void messageSent(const QByteArray& message);
    void stateChanged(QAbstractSocket::SocketState state);
 
private:
    void wire(void) {
        QObject::connect(sock, &QTcpSocket::stateChanged, this, &TcpSocket::stateChanged);
        QObject::connect(sock, &QTcpSocket::readyRead, this, &TcpSocket::readyRead);
    }

    QTcpSocket* sock;
};