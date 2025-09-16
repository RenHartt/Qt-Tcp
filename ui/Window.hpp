#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>

class Window : public QWidget {
    Q_OBJECT
public:
    explicit Window(QWidget* parent = nullptr) : QWidget(parent) {
    // layout principal horizontal : logs à gauche, connexion à droite
    mainLayout = new QHBoxLayout(this);

    // --- partie logs ---
    logLayout = new QVBoxLayout();
    log = new QPlainTextEdit(this);
    log->setReadOnly(true);
    messageLayout = new QHBoxLayout();
    message = new QLineEdit(this);
    send = new QPushButton("Send", this);
    messageLayout->addWidget(message);
    messageLayout->addWidget(send);

    logLayout->addWidget(log);
    logLayout->addLayout(messageLayout);
    mainLayout->addLayout(logLayout);

    // --- partie connexion ---
    connexionLayout = new QVBoxLayout();
    ip = new QLineEdit(this);
    ip->setPlaceholderText("Adresse IP");
    port = new QLineEdit(this);
    port->setPlaceholderText("Port");
    connexion = new QPushButton("Connexion", this);

    connexionLayout->addWidget(ip);
    connexionLayout->addWidget(port);
    connexionLayout->addWidget(connexion);
    mainLayout->addLayout(connexionLayout);
}


private:
    QHBoxLayout* mainLayout;
    QVBoxLayout* logLayout;
    QPlainTextEdit* log;
    QHBoxLayout* messageLayout;
    QLineEdit* message;
    QPushButton* send;   
    QVBoxLayout* connexionLayout;
    QLineEdit* ip;
    QLineEdit* port;
    QPushButton* connexion;
};