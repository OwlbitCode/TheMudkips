#include "aarena.h"
#include "ui_aarena.h"

aArena::aArena(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aArena)
{
    ui->setupUi(this);
}

aArena::~aArena()
{
    delete ui;
}
