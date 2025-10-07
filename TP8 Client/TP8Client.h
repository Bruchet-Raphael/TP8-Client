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
    //gestion connexion et deconnexion
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError socketError); // Permet de gerer les erreurs
    //demmande de la t'emperature et de l'humidité
    void onTempEnCButtonClicked();
    void onTempEnFButtonClicked();
    void onHumButtonClicked();
    void onSocketReadyRead();
};

