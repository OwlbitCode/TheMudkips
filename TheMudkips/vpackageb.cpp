#include "vpackageb.h"
#include "ui_vpackageb.h"

vPackageB::vPackageB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vPackageB)
{
    ui->setupUi(this);
    // Get database connection
    myDB = QSqlDatabase::database();
    defaultPackage(); // call default view set up
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
    //qDebug() << "HELLO I'm HERE!";
    //qDebug() << "TEAM NUM YO: " << teamNum;
    simulationWindow = new vSimulation(sortedTeams, sortedDistance, teamNum);
    simulationWindow->show();
    //qDebug() << "shits and giggles!";
    this->close();
}


void vPackageB::defaultPackage()
{
    // Create new database query
    QSqlQuery * qry = new QSqlQuery(myDB);

    teamNum = 1;

    //int i = 1; //iterator
    // Set up the query to create ordered list of teams, except startTeam


    //get total team count

    //Get the total team Count:
    qry->prepare("SELECT DISTINCT `Beg Team` "
                 "FROM Distances "
                 "WHERE `Beg Team` != '"+startTeam+"'"
                 "ORDER BY `Beg Team` COLLATE NOCASE ASC ");

    // Execute query if valid
    if(qry->exec())
    {
        // Populating list from query
        while(qry->next())
        {
            teamNum++;

        }
    }
    else
    {
        qDebug() << ("vpackagec Error: qry failed.");
    }

        qDebug() << "team num" << teamNum;



    //Assign values into dynamic array

        sortedTeams = new QString[teamNum]; // new object for dynamic
                                             // team array
        sortedDistance = new double[teamNum];  // new object for dynamic
                                             // distance array

        sortedTeams[0] = startTeam;
        sortedDistance[0] = 0;

        int i = 1;

    qry->prepare("SELECT DISTINCT `Beg Team` "
                 "FROM Distances "
                 "WHERE `Beg Team` != '"+startTeam+"'"
                 "ORDER BY `Beg Team` COLLATE NOCASE ASC ");

    // Execute query if valid
    if(qry->exec())
    {
        // Populating list from query

        while(qry->next())
        {
            sortedTeams[i] = qry->value(0).toString();
            sortedDistance[i] = qry->value(3).toDouble();
            i++; //iterate
        }

        /*
        //delete later test below
        qry->next();
        sortedTeams[i] = qry->value(0).toString();
        sortedDistance[i] = qry->value(3).toDouble();
        i++; //iterate
        qry->next();
        sortedTeams[i] = qry->value(0).toString();
        sortedDistance[i] = qry->value(3).toDouble();
        //delete above
        */

    }
    else
    {
        qDebug() << ("vpackagec Error: qry failed.");
    }



    // Load all selected, sorted teams into sorted list view
    for(int i = 0; i < teamNum; i++)
    {
        ui->sortedTeamList->addItem(sortedTeams[i]);
    }



}




