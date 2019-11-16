#include "vpackagea.h"
#include "ui_vpackagea.h"

vPackageA::vPackageA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vPackageA)
{
    ui->setupUi(this);

    // Get database connection
    myDB = QSqlDatabase::database();
}

vPackageA::~vPackageA()
{
    delete ui;
}

void vPackageA::on_cancelButton_clicked()
{
    this->close();
}

void vPackageA::on_startButton_clicked()
{
    simulationWindow = new vSimulation;
    simulationWindow->show();

    this->close();
}
