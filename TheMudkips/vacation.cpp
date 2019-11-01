#include "vacation.h"
#include "ui_vacation.h"

Vacation::Vacation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vacation)
{
    ui->setupUi(this);
}

Vacation::~Vacation()
{
    delete ui;
}
