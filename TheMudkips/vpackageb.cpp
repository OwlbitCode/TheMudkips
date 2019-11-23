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
    simulationWindow = new vSimulation;
    simulationWindow->show();

    this->close();
}


void vPackageB::defaultPackage()
{
    // Create new database query
    QSqlQuery * qry = new QSqlQuery(myDB);

    int teamNum = 1;
    int i = 1; //iterator
    // Set up the query to create ordered list of teams, except startTeam

    //Get the Count:
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

        qDebug() << "team Num" << teamNum;

    //Assign values into dynamic array

        sortedTeams = new QString[teamNum]; // new object for dynamic
                                             // team array
        sortedDistance = new int[teamNum];  // new object for dynamic
                                             // distance array

        sortedTeams[0] = startTeam;
        sortedDistance[0] = 0;

    //Get the Count:
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
            i++; //iterate
        }
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






