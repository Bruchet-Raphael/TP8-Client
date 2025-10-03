#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TP8Client.h"
#include <qtcpsocket.h>

class TP8Client : public QMainWindow
{
    Q_OBJECT

public:
    TP8Client(QWidget *parent = nullptr);
    ~TP8Client();

private:
    Ui::TP8ClientClass ui;
    QTcpSocket* socket;
private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError socketError);
};

