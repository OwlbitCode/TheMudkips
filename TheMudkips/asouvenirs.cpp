#include "asouvenirs.h"
#include "ui_asouvenirs.h"

aSouvenirs::aSouvenirs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aSouvenirs)
{
    ui->setupUi(this);
}

aSouvenirs::~aSouvenirs()
{
    delete ui;
}
