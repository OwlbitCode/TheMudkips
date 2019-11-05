#include "nbateams.h"
#include "ui_nbateams.h"
#include "QtSql"
#include "databasemanager.h"
#include "QtDebug"

nbaTeams::nbaTeams(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nbaTeams)
{
    ui->setupUi(this);
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
        databaseManager db;
        db.openDB();

        QSqlQuery* qry = new QSqlQuery(db.currentDB());

        qry->prepare("select * from 'Team Info' where `Conference` = 'Eastern'");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);

        db.closeDB();
    }
    else
    {
        QSqlQueryModel* model = new QSqlQueryModel();

        qDebug() << team;
        databaseManager db;
        db.openDB();

        QSqlQuery* qry = new QSqlQuery(db.currentDB());


        qry->prepare("select * from 'Team Info' where `Team Name` = '"+team+"'");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);

        db.closeDB();
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

        databaseManager db;
        db.openDB();

        QSqlQuery* qry = new QSqlQuery(db.currentDB());


        qry->prepare("select * from 'Team Info' where `Conference` = 'Western'");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);
        db.closeDB();
    }
    else
    {
        ui->dataView->setSortingEnabled(true);
        QSqlQueryModel* model = new QSqlQueryModel();

        databaseManager db;
        db.openDB();

        QSqlQuery* qry = new QSqlQuery(db.currentDB());

        qry->prepare("select * from 'Team Info' where `Team Name` = '"+team+"'");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);

        db.closeDB();
    }
}
