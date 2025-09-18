#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDateTime>

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

    void onDisconnect(void) {
        sock->disconnectFromHost();
    }

    void onSend(const QByteArray& data) {
        sock->write(data);
        QString date(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
        QString message(data);
        emit sendLog("[" + date + "] TX -> " + message);
    }

    void onReadyRead(void) {
        QString date(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
        emit sendLog("[" + date + "] RX -> " + QString(sock->readLine()));
    }
    
signals:
    void sendLog(const QString& log);

private slots:
    void onSocketStateChanged(QAbstractSocket::SocketState state) {
        QString date(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
        QString log("[" + date + "] STATE -> ");
        switch (state) {
            case QAbstractSocket::UnconnectedState:
                emit sendLog(log + "UNCONNECTED");
                break;
            case QAbstractSocket::HostLookupState:
                emit sendLog(log + "HOST LOOK UP");
                break;
            case QAbstractSocket::ConnectingState:
                emit sendLog(log + "CONNECTING");
                break;
            case QAbstractSocket::ConnectedState:
                emit sendLog(log + "CONNECTED");
                break;
            case QAbstractSocket::ClosingState:
                emit sendLog(log + "CLOSING");
                break;
            default:
                break;
        }
    }
    
private:
    void wire(void) {
        QObject::connect(sock, &QTcpSocket::stateChanged, this, &TcpSocket::onSocketStateChanged);
        QObject::connect(sock, &QTcpSocket::readyRead, this, &TcpSocket::onReadyRead);
    }

    QTcpSocket* sock;
};