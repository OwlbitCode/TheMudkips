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
    currTeamNum=0;
    //int i = 1; //iterator
    // Set up the query to create ordered list of teams, except startTeam

    //Get the Count:
    qry->prepare("SELECT * "
                 "FROM Distances "
                 "WHERE `Beg Team` == '"+startTeam+"'"
                 "ORDER BY `Beg Team` COLLATE NOCASE ASC ");

    // Execute query if valid
    if(qry->exec())
    {
        // Populating list from query
        while(qry->next())
        {
            currTeamNum++;

        }
    }
    else
    {
        qDebug() << ("vpackagec Error: qry failed.");
    }


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


        qDebug() << "curr team Num" << currTeamNum;
        qDebug() << "team num" << teamNum;



    //Assign values into dynamic array

        sortedTeams = new QString[teamNum]; // new object for dynamic
                                             // team array
        sortedDistance = new double[teamNum];  // new object for dynamic
                                             // distance array

        sortedTeams[0] = startTeam;
        sortedDistance[0] = 0;

        /*
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
            sortedDistance[i] = qry->value(3).toDouble();
            i++; //iterate
        }
    }
    else
    {
        qDebug() << ("vpackagec Error: qry failed.");
    }
*/

    //Testing

        QSqlQuery qry2;
        qry2.prepare("SELECT * "
                    "FROM Distances "
                    "WHERE `Beg Team`= '"+startTeam+"'"
                    "ORDER BY Distance ASC");
        qry2.exec();
        qry2.next();

       QString idValue = qry2.value(0).toString();
       qDebug() << "IdVALUE" << idValue;
       double distance =  qry2.value(3).toDouble();
       qDebug() << "Distance" << distance;


        /*
         *


    for(int i = 1; i<teamNum;i++)
      {
            QSqlQuery qry2;
            qry2.prepare("SELECT * "
                        "FROM Distances "
                        "WHERE `Beg Team`= '"+startTeam+"'"
                        "ORDER BY Distance ASC");
            qry2.exec();
            qry2.next();

           QString idValue = qry2.value(0).toString();
           qDebug() << "IdVALUE" << idValue;
           double distance =  qry2.value(3).toInt();
           qDebug() << "Distance" << distance;

          for(int j=0; j<i; j++)
          {
              //qDebug() <<"here" << arr[j] << " " << idValue;
              if (idValue==sortedTeams[j])
              {
                  //qDebug() <<"arr[j" << arr[j];
                  qry2.next();
                  idValue = qry2.value(0).toString();
                  distance = qry2.value(3).toDouble();
                  j=-1;
              }

          }



            //qDebug() << "ID VALUE" << idValue;

            sortedTeams[i] = idValue;
            sortedDistance[i] = distance;

            startTeam = idValue; //assign test city to the new city


    }
*/


    // Load all selected, sorted teams into sorted list view
    for(int i = 0; i < teamNum; i++)
    {
        ui->sortedTeamList->addItem(sortedTeams[i]);
    }



}




