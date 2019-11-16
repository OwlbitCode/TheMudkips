#include "vpackagec.h"
#include "ui_vpackagec.h"

vPackageC::vPackageC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vPackageC)
{
    ui->setupUi(this);

    // Get database connection
    myDB = QSqlDatabase::database();
}

vPackageC::~vPackageC()
{
    delete ui;
}

void vPackageC::on_cancelButton_clicked()
{
    this->close();
}

void vPackageC::on_startButton_clicked()
{
    simulationWindow = new vSimulation;
    simulationWindow->show();

    this->close();
}
