#include "vdfs.h"
#include "ui_vdfs.h"

vDFS::vDFS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vDFS)
{
    ui->setupUi(this);
}

vDFS::~vDFS()
{
    delete ui;
}
