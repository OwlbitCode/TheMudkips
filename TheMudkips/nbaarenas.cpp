#include "nbaarenas.h"
#include "ui_nbaarenas.h"

nbaArenas::nbaArenas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nbaArenas)
{
    ui->setupUi(this);
}

nbaArenas::~nbaArenas()
{
    delete ui;
}
