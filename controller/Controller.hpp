#pragma once

#include "TcpSocket.hpp"
#include "Window.hpp"

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

private:
    void wire() {
        connect(win, &Window::requestConnect, client, &TcpSocket::onConnect);
        connect(client, &TcpSocket::sendLog, win, &Window::print);
    }

    TcpSocket* client;
    Window* win;

};