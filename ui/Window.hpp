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
        setupUi();
        wire();
    }

signals:
    void requestConnect(const QString& host, quint16 port);

private:
    void setupUi(void) {
        mainLayout = new QHBoxLayout(this);
    
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

    void wire(void) {
        connect(connexion, &QPushButton::clicked, this, [this] {
            emit requestConnect(ip->text().trimmed(), port->text().toUShort());
        });
    }

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