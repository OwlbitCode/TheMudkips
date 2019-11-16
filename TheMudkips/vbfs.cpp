#include "vbfs.h"
#include "ui_vbfs.h"

vBFS::vBFS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vBFS)
{
    ui->setupUi(this);
}

vBFS::~vBFS()
{
    delete ui;
}
