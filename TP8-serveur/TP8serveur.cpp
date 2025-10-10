#include "TP8serveur.h"
#include <QRandomGenerator>

TP8serveur::TP8serveur(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    server = new QTcpServer(this);
    socket = new QTcpSocket(this);
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
    QObject::disconnect(obj, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
    QObject::disconnect(obj, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
    obj->deleteLater();
}

void TP8serveur::onClientReadyRead()
{
    QTcpSocket* obj = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = obj->readAll();
    QString message = QString::fromUtf8(data).trimmed();

    QString response;

    if (message.startsWith("Tdxx?")) // Température
    {
        int temperature = QRandomGenerator::global()->bounded(-20, 37); // entre -20 et 37°C
        response = QString("Tdxx:%1").arg(temperature);
        obj->write(response.toUtf8());
    }
    else if (message.startsWith("Tfxx?")) // Température en Fahrenheit
    {
        int tempF = QRandomGenerator::global()->bounded(-4, 98.6); // entre -4°F et 98.6°F
        response = QString("Tfxx:%1").arg(tempF);
        obj->write(response.toUtf8());
    }
    else if (message.startsWith("Hrxx?")) // Humidité
    {
        int humidite = QRandomGenerator::global()->bounded(0, 100); // entre 0 et 100%
        response = QString("Hrxx:%1").arg(humidite);
        obj->write(response.toUtf8());
    }

}
