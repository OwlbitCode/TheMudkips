#include "vpackageb.h"
#include "ui_vpackageb.h"

vPackageB::vPackageB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vPackageB)
{
    ui->setupUi(this);

    // Get database connection
    myDB = QSqlDatabase::database();
}

vPackageB::~vPackageB()
{
    delete ui;
}

void vPackageB::on_cancelButton_clicked()
{
    this->close();
}

void vPackageB::on_startButton_clicked()
{
    simulationWindow = new vSimulation;
    simulationWindow->show();

    this->close();
}
