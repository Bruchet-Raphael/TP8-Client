#include "TP8Client.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TP8Client window;
    window.show();
    return app.exec();
}
