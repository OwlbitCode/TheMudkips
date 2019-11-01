#include "nbateams.h"
#include "ui_nbateams.h"

nbaTeams::nbaTeams(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nbaTeams)
{
    ui->setupUi(this);
}

nbaTeams::~nbaTeams()
{
    delete ui;
}
