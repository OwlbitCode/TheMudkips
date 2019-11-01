#include "ateam.h"
#include "ui_ateam.h"

aTeam::aTeam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aTeam)
{
    ui->setupUi(this);
}

aTeam::~aTeam()
{
    delete ui;
}
