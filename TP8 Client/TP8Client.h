#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TP8Client.h"

class TP8Client : public QMainWindow
{
    Q_OBJECT

public:
    TP8Client(QWidget *parent = nullptr);
    ~TP8Client();

private:
    Ui::TP8ClientClass ui;
};

