#include "nbaconfdiv.h"
#include "ui_nbaconfdiv.h"

nbaConfDiv::nbaConfDiv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nbaConfDiv)
{
    ui->setupUi(this);
    myDB = QSqlDatabase::database();
}

nbaConfDiv::~nbaConfDiv()
{
    delete ui;
}

void nbaConfDiv::on_teamComboBox_activated(const QString &arg1)
{
    QString team = arg1;
    if(team == "All Teams")
    {
        QSqlQueryModel* model = new QSqlQueryModel();

        qDebug() << team;
        QSqlQuery * qry = new QSqlQuery(myDB);

        qry->prepare("select * from 'Team Info'");
        qry->exec();

        model->setQuery(*qry);
        ui->dataView->setModel(model);

        ui->sortYearButton->setEnabled(true);
        ui->sortNameButton->setEnabled(true);
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

        ui->sortYearButton->setEnabled(false);
        ui->sortNameButton->setEnabled(false);
    }
}

void nbaConfDiv::on_sortNameButton_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery * qry = new QSqlQuery(myDB);

    qry->prepare("select * from 'Team Info' order by `Team Name`");
    qry->exec();

    model->setQuery(*qry);
    ui->dataView->setModel(model);
}

void nbaConfDiv::on_sortYearButton_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();

   QSqlQuery * qry = new QSqlQuery(myDB);

    //sorted by team name and their arena names, the year they joined the league,   sorted by year in ascending order.
    qry->prepare("select `Team Name`, `Arena Name`, `Joined League` from 'Team Info' order by `Joined League` ASC");
    qry->exec();

    model->setQuery(*qry);
    ui->dataView->setModel(model);
}
