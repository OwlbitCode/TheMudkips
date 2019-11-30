#include "ateam.h"
#include<addteam.h>
#include "ui_ateam.h"
#include<QDebug>
aTeam::aTeam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aTeam)
{
    ui->setupUi(this);
    myDb=QSqlDatabase::database();

    QSqlQuery* query = new QSqlQuery(myDb);
    QSqlQueryModel* model = new QSqlQueryModel;
    query->prepare("select `Team Name` from 'Team Info'");
    if(query->exec()){std::cout<<"query executed";}
    else{std::cout<<"query failed";}
    model->setQuery(*query);
    ui->comboBox->setModel(model);

    QSqlQuery* qry = new QSqlQuery(myDb);
    QSqlQueryModel* mdl = new QSqlQueryModel;
    qry->prepare("select * from 'Team Info'");
    if(qry->exec()){std::cout<<"Tabel loaded";}
    else{std::cout<<"Table failed to load";}
    mdl->setQuery(*qry);
    ui->tableView->setModel(mdl);
}

aTeam::~aTeam()
{
    delete ui;

}

void aTeam::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();


    QSqlQuery qry;
    qry.prepare("select * from Team Info where Team Name = '"+val+"' or Division = '"+val+"' or Conference = '"+val+"'"
                     "or Location = '"+val+"' or Arena Name = '"+val+"' or Stadium Capacity = '"+val+"' or Joined League = '"+val+"' "
                        "or Coach = '"+val+"'");

}


void aTeam::on_comboBox_currentIndexChanged(const QString &arg1) //loads team data into line_edits
{
    QString name = ui->comboBox->currentText();
    QSqlQuery* qry = new QSqlQuery(myDb);

    qry->prepare("select * from 'Team Info' where `Team Name` = '"+name+"'");
    qry->exec();
    if(qry->exec()){

    while(qry->next())
    {
        ui->lineEdit->setText(qry->value(0).toString());
        ui->lineEdit_2->setText(qry->value(1).toString());
        ui->lineEdit_3->setText(qry->value(2).toString());
        ui->lineEdit_4->setText(qry->value(3).toString());
        ui->lineEdit_5->setText(qry->value(4).toString());
        ui->lineEdit_6->setText(qry->value(5).toString());
        ui->lineEdit_7->setText(qry->value(6).toString());
        ui->lineEdit_8->setText(qry->value(7).toString());
    }
    }
    else{
        std::cout << "failed to connect";
    }
}

void aTeam::on_pushButton_clicked() //update the table
{
    QString name,coach,division,year,arena,conference,location,stadiumcap;
    conference = ui->lineEdit->text();
    division = ui->lineEdit_2->text();
    name = ui->lineEdit_3->text();
    location = ui->lineEdit_4->text();
    arena = ui->lineEdit_5->text();
    stadiumcap = ui->lineEdit_6->text();
    year = ui->lineEdit_7->text();
    coach = ui->lineEdit_8->text();

    QSqlQuery* query = new QSqlQuery(myDb);
    query->prepare("update 'Team Info' set `Team Name` = '"+name+"', Conference ='"+conference+"', Division='"+division+"', `Team Name`='"+name+"' , Location='"+location+"', `Arena Name`='"+arena+"', `Stadium Capacity`='"+stadiumcap+"', `Joined League`='"+year+"', Coach='"+coach+"' where `Team Name` = '"+name+"'");
            if(query->exec()){
        std::cout << "updated succesfully";

        QSqlQuery* qry = new QSqlQuery(myDb);
        QSqlQueryModel* mdl = new QSqlQueryModel;
        qry->prepare("select * from 'Team Info'");
        if(qry->exec()){std::cout<<"Tabel loaded";}
        else{std::cout<<"Table failed to load";}
        mdl->setQuery(*qry);
        ui->tableView->setModel(mdl);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
            }
    else{std::cout<<"failed to update";}
}

void aTeam::on_pushButton_3_clicked() //Delete a team
{
    QString name = ui->comboBox->currentText();
    QString variable = name + " Store";
    QSqlQuery* query = new QSqlQuery(myDb);
    query->prepare("delete from 'Team Info' where `Team Name` = '"+name+"'");
    if(query->exec())
    {
        std::cout << "deleted succesfully";

        QSqlQuery* qry = new QSqlQuery(myDb);
        QSqlQueryModel* mdl = new QSqlQueryModel;
        qry->prepare("select * from 'Team Info'");
        if(qry->exec()){std::cout<<"Tabel loaded";}
        else{std::cout<<"Table failed to load";}
        mdl->setQuery(*qry);
        ui->tableView->setModel(mdl);

        qry->clear();
        std::string test = variable.toStdString();
        std::cout << std::endl << test;
        qry->prepare("delete ''"+variable+"''");
    }
    else {std::cout<<"failed to delete";}
}



void aTeam::on_pushButton_2_clicked() //add a team
{

}
