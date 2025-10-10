#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TP8serveur.h"
#include "qtcpserver.h"
#include "qtcpsocket.h"

class TP8serveur : public QMainWindow
{
    Q_OBJECT

public:
    TP8serveur(QWidget *parent = nullptr);
    ~TP8serveur();

private:
    Ui::TP8serveurClass ui;
    QTcpServer* server;

public slots:
    void onServerNewConnection();
    void onClientDisconnected();
    void onClientReadyRead();
};

