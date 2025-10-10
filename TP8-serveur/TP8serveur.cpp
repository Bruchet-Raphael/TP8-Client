#include "TP8serveur.h"

TP8serveur::TP8serveur(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    server = new QTcpServer(this);
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));
    server->listen(QHostAddress::AnyIPv4, 6900);
}

TP8serveur::~TP8serveur()
{}

void TP8serveur::onServerNewConnection()
{
    ui.serverStat->setText("Un client s'est connecte");
    QTcpSocket* client = server->nextPendingConnection();
    QObject::connect(client, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
    QObject::connect(client, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
}

void TP8serveur::onClientDisconnected()
{
    ui.serverStat->setText("Un client s'est deconnecte");
    QTcpSocket* obj = qobject_cast<QTcpSocket*>(sender());
}

void TP8serveur::onClientReadyRead()
{
    QTcpSocket* obj = qobject_cast<QTcpSocket*>(sender());
}
