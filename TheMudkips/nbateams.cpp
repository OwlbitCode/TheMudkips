#include "nbateams.h"
#include "ui_nbateams.h"


nbaTeams::nbaTeams(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nbaTeams)
{
    ui->setupUi(this);
    myDB = QSqlDatabase::database();
}

nbaTeams::~nbaTeams()
{
    delete ui;
}

void nbaTeams::on_pushButton_2_clicked()
{
        QSqlQueryModel* model = new QSqlQueryModel();

        QSqlQuery * qry = new QSqlQuery(myDB);
        qry->prepare("select * from 'Team Info' where `Conference` = 'Eastern' order by `Team Name`");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);
}

void nbaTeams::on_pushButton_clicked()
{
        qDebug() << "ASD";
        QSqlQueryModel* model = new QSqlQueryModel();

        QSqlQuery * qry = new QSqlQuery(myDB);


        qry->prepare("select * from 'Team Info' where `Division` = 'Southeast' and `Conference` = 'Eastern' order by `Team Name`");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);
}
