#include "nbasouvenirs.h"
#include "ui_nbasouvenirs.h"

nbaSouvenirs::nbaSouvenirs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nbaSouvenirs)
{
    ui->setupUi(this);
}

nbaSouvenirs::~nbaSouvenirs()
{
    delete ui;
}
