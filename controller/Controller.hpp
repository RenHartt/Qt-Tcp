#pragma once

#include "TcpSocket.hpp"
#include "Window.hpp"
#include <QDateTime>

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller(QObject* parent = nullptr) : QObject(parent) {
        win = new Window;
        client = new TcpSocket(this);
        wire();
    }

    void show(void) {
        win->show();
    }

signals:
    void printLog(const QString& log);

public slots:
    void onStateChanged(QAbstractSocket::SocketState state) {
        QString date(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
        QString log("[" + date + "] STATE -> ");
        switch (state) {
            case QAbstractSocket::UnconnectedState:
                emit printLog(log + "UNCONNECTED");
                break;
            case QAbstractSocket::HostLookupState:
                emit printLog(log + "HOST LOOK UP");
                break;
            case QAbstractSocket::ConnectingState:
                emit printLog(log + "CONNECTING");
                break;
            case QAbstractSocket::ConnectedState:
                emit printLog(log + "CONNECTED");
                break;
            case QAbstractSocket::ClosingState:
                emit printLog(log + "CLOSING");
                break;
            default:
                break;
        }
    }

    void onMessageReceived(const QByteArray& message) {
        QString date(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
        emit printLog("[" + date + "] RX -> " + QString(message));
    }

    void onMessageSent(const QByteArray& message) {
        QString date(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
        emit printLog("[" + date + "] TX -> " + QString(message));
    }

private:
    void wire() {
        connect(win, &Window::requestConnect, client, &TcpSocket::connectToHost);
        connect(win, &Window::requestDisconnect, client, &TcpSocket::disconnectFromHost);
        connect(win, &Window::requestSend, client, &TcpSocket::onSend);
        connect(client, &TcpSocket::stateChanged, this, &Controller::onStateChanged);
        connect(client, &TcpSocket::messageReceived, this, &Controller::onMessageReceived);
        connect(client, &TcpSocket::messageSent, this, &Controller:: onMessageSent);        
        connect(this, &Controller::printLog, win, &Window::printLog);
    }

    TcpSocket* client;
    Window* win;

};