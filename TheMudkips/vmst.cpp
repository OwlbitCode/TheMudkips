#include "vmst.h"
#include "ui_vmst.h"

vMST::vMST(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vMST)
{
    ui->setupUi(this);
}

vMST::~vMST()
{
    delete ui;
}
