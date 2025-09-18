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
    void requestDisconnect(void);
    void requestSend(const QByteArray& message);

public slots:
    void print(const QString& log) {
        logPanel->appendPlainText(log);
    }

private:
    void setupUi(void) {
        mainLayout = new QHBoxLayout(this);
    
        logLayout = new QVBoxLayout();
        logPanel = new QPlainTextEdit(this);
        logPanel->setReadOnly(true);
        messageLayout = new QHBoxLayout();
        message = new QLineEdit(this);
        send = new QPushButton("Send", this);
        send->setStyleSheet("background-color: blue; color: black;");
        messageLayout->addWidget(message);
        messageLayout->addWidget(send);
    
        logLayout->addWidget(logPanel);
        logLayout->addLayout(messageLayout);
        mainLayout->addLayout(logLayout);
    
        connexionLayout = new QVBoxLayout();
        ip = new QLineEdit(this);
        ip->setPlaceholderText("Adresse IP");
        port = new QLineEdit(this);
        port->setPlaceholderText("Port");
        connection = new QPushButton("Connection", this);
        connection->setStyleSheet("background-color: green; color: white;");
        disconnection = new QPushButton("Disonnection", this);
        disconnection->setStyleSheet("background-color: red; color: white;");
        connexionLayout->addWidget(ip);
        connexionLayout->addWidget(port);
        connexionLayout->addWidget(connection);
        connexionLayout->addWidget(disconnection);
       
        mainLayout->addLayout(connexionLayout);
    }

    void wire(void) {
        connect(connection, &QPushButton::clicked, this, [this] {
            emit requestConnect(ip->text().trimmed(), port->text().toUShort());
        });
        connect(disconnection, &QPushButton::clicked, this, [this] {
            emit requestDisconnect();
        });
        connect(send, &QPushButton::clicked, this, [this] {
            emit requestSend(message->text().toUtf8());
        });
        connect(send, &QPushButton::clicked, message, &QLineEdit::clear);
    }

    QHBoxLayout* mainLayout;
    QVBoxLayout* logLayout;
    QPlainTextEdit* logPanel;
    QHBoxLayout* messageLayout;
    QLineEdit* message;
    QPushButton* send;   
    QVBoxLayout* connexionLayout;
    QLineEdit* ip;
    QLineEdit* port;
    QPushButton* connection;
    QPushButton* disconnection;
};