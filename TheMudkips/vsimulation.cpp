#include "vsimulation.h"
#include "ui_vsimulation.h"

vSimulation::vSimulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vSimulation)
{
    ui->setupUi(this);

    // Get database connection
    myDB = QSqlDatabase::database();
}

vSimulation::~vSimulation()
{
    delete ui;
}

void vSimulation::on_cancelButton_clicked()
{
    this->close();
}

void vSimulation::on_endButton_clicked()
{
    this->close();
}
