#include "nbacoaches.h"
#include "ui_nbacoaches.h"

nbaCoaches::nbaCoaches(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nbaCoaches)
{
    ui->setupUi(this);
}

nbaCoaches::~nbaCoaches()
{
    delete ui;
}
