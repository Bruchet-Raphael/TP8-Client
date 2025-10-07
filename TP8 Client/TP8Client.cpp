#include "TP8Client.h"

TP8Client::TP8Client(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    socket = new QTcpSocket(this); 
    // Connection des boutons au differente fonction
    connect(ui.connectButton, &QPushButton::clicked, this, &TP8Client::onConnectButtonClicked);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &TP8Client::onDisconnectButtonClicked);
    connect(ui.tempEnC, &QPushButton::clicked, this, &TP8Client::onTempEnCButtonClicked);
    connect(ui.tempEnF, &QPushButton::clicked, this, &TP8Client::onTempEnFButtonClicked);
    connect(ui.humButton, &QPushButton::clicked, this, &TP8Client::onHumButtonClicked);
    connect(socket, &QTcpSocket::readyRead, this, &TP8Client::onSocketReadyRead);
    QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    QObject::connect(socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}

TP8Client::~TP8Client()
{}

void TP8Client::onConnectButtonClicked()
{
    QString ip = ui.ip->text(); // Recuperation de l'ip du serveur
    QString port = ui.port->text(); // Recuperation du port du serveur

    bool ok;
    int portAsInt = port.toInt(&ok); // Conversion du port (char -> int)
    if (ok)
    {
        socket->connectToHost(ip, portAsInt); // Connection au serveur
    }
}

void TP8Client::onDisconnectButtonClicked()
{
    if (socket->state() == QAbstractSocket::ConnectedState) // Verification de la connexion
    {
        socket->disconnectFromHost(); // Deconnexion du serveur
        ui.connexionStat->setText("Deconnexion");
    }
    else {
        ui.connexionStat->setText("Pas de connexion active."); // Informe l'utilisateur qu'aucune connexion n'est active
    }
}

void TP8Client::onSocketConnected()
{
    ui.connexionStat->setText("Connecte"); // Informe l'utilisateur qui l'est connecter au serveur
}

void TP8Client::onSocketDisconnected()
{
    ui.connexionStat->setText("Deconnecte."); // Informe l'utilisateur qui l'est déconnecter du serveur
}

void TP8Client::onSocketError(QAbstractSocket::SocketError socketError)
{
    ui.connexionStat->setText("Erreur : " + socket->errorString()); // Affiche les éventuelles erreurs
}

void TP8Client::onTempEnCButtonClicked() // Demmande la temperature (en °C) au serveur
{
    ui.temp->setText("Temperature : en attente");
    QString message = "Tdxx?";
    socket->write(message.toUtf8());
}

void TP8Client::onTempEnFButtonClicked() // Demmande la temperature (en °F) au serveur
{
    ui.temp->setText("Temperature : en attente");
    QString message = "Tfxx?";
    socket->write(message.toUtf8());   
}

void TP8Client::onHumButtonClicked() // Demmande l'humidité au serveur
{
    ui.hum->setText("Humidite : en attente");
    QString message = "Hrxx?";
    socket->write(message.toUtf8());
}

void TP8Client::onSocketReadyRead()
{
    QByteArray data = socket->readAll(); // Écoute les messages du serveur
    QString message = QString::fromUtf8(data).trimmed();

    if (message.startsWith("Tdxx")) // Si le message commence par "Tdxx"
    {
        QString valeur = message.mid(5); // On ne recupere pas les 5 1er caratères 
        ui.temp->setText("Temperature : " + valeur + " C"); // On affiche la valeur et l'unité
    }
    else if (message.startsWith("Tfxx")) // Si le message commence par "Tfxx"
    {
        QString valeur = message.mid(5); // On ne recupere pas les 5 1er caratères 
        ui.temp->setText("Temperature : " + valeur + " F"); // On affiche la valeur et l'unité
    }
    else if (message.startsWith("Hrxx")) // Si le message commence par "Hrxx"
    {
        QString valeur = message.mid(5); // On ne recupere pas les 5 1er caratères 
        ui.hum->setText("Humidite : " + valeur + " %"); // On affiche la valeur et l'unité
    }
    else 
    {
        ui.connexionStat->setText("Message reçu : " + message); // sinon on ecrit le message recu dans l'etat de la connexion
    }
}