#include "TP8serveur.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TP8serveur window;
    window.show();
    return app.exec();
}
