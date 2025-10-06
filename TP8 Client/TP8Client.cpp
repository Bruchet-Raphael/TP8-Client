#include "TP8Client.h"

TP8Client::TP8Client(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    socket = new QTcpSocket(this);
    connect(ui.connectButton, &QPushButton::clicked, this, &TP8Client::onConnectButtonClicked);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &TP8Client::onDisconnectButtonClicked);
    connect(ui.tempEnC, &QPushButton::clicked, this, &TP8Client::onTempEnCButtonClicked);
    connect(ui.tempEnF, &QPushButton::clicked, this, &TP8Client::onTempEnFButtonClicked);
    connect(ui.humButton, &QPushButton::clicked, this, &TP8Client::onHumButtonClicked);
    QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    QObject::connect(socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}

TP8Client::~TP8Client()
{}

void TP8Client::onConnectButtonClicked()
{
    QString ip = ui.ip->text();
    QString port = ui.port->text();

    bool ok;
    int portAsInt = port.toInt(&ok);
    if (ok)
    {
        socket->connectToHost(ip, portAsInt);
    }
}

void TP8Client::onDisconnectButtonClicked()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
        ui.connexionStat->setText("Deconnexion");
    }
    else {
        ui.connexionStat->setText("Pas de connexion active.");
    }
}

void TP8Client::onSocketConnected()
{
    ui.connexionStat->setText("Connecte");
}

void TP8Client::onSocketDisconnected()
{
    ui.connexionStat->setText("Deconnecte.");
}

void TP8Client::onSocketError(QAbstractSocket::SocketError socketError)
{
    ui.connexionStat->setText("Erreur : " + socket->errorString());
}

void TP8Client::onTempEnCButtonClicked()
{
    ui.temp->setText("Temperature : en attente");
    QString message = "Tdxx?";
    socket->write(message.toUtf8());
}

void TP8Client::onTempEnFButtonClicked()
{
    ui.temp->setText("Temperature : en attente");
    QString message = "Tfxx?";
    socket->write(message.toUtf8());
}

void TP8Client::onHumButtonClicked()
{
    ui.hum->setText("Humidite : en attente");
    QString message = "Hrxx?";
    socket->write(message.toUtf8());
}
