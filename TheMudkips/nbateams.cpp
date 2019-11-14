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

void nbaTeams::on_EasternComboBox_activated(const QString &arg1)
{
    ui->dataView->setSortingEnabled(true);
    ui->westernComboBox->setCurrentIndex(0);
    QString team = arg1;
    if(team == "All Eastern Division Teams")
    {
        QSqlQueryModel* model = new QSqlQueryModel();

        qDebug() << team;

        QSqlQuery * qry = new QSqlQuery(myDB);
        qry->prepare("select * from 'Team Info' where `Conference` = 'Eastern' order by `Team Name`");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);

    }
    else
    {
        QSqlQueryModel* model = new QSqlQueryModel();

        qDebug() << team;
        QSqlQuery * qry = new QSqlQuery(myDB);


        qry->prepare("select * from 'Team Info' where `Team Name` = '"+team+"'");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);
    }
}

void nbaTeams::on_westernComboBox_activated(const QString &arg1)
{
    ui->dataView->setSortingEnabled(true);
    ui->EasternComboBox->setCurrentIndex(0);
    QString team = arg1;

    if(team == "All Western Division Teams")
    {
        qDebug() << "ASD";
        QSqlQueryModel* model = new QSqlQueryModel();

        QSqlQuery * qry = new QSqlQuery(myDB);


        qry->prepare("select * from 'Team Info' where `Conference` = 'Western' order by `Team Name`");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);
    }
    else
    {
        ui->dataView->setSortingEnabled(true);
        QSqlQueryModel* model = new QSqlQueryModel();

        QSqlQuery * qry = new QSqlQuery(myDB);

        qry->prepare("select * from 'Team Info' where `Team Name` = '"+team+"'");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);
    }
}
