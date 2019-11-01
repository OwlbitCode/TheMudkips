#include "nbaconfdiv.h"
#include "ui_nbaconfdiv.h"

nbaConfDiv::nbaConfDiv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nbaConfDiv)
{
    ui->setupUi(this);
}

nbaConfDiv::~nbaConfDiv()
{
    delete ui;
}
