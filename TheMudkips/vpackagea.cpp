#include "vpackagea.h"
#include "ui_vpackagea.h"

vPackageA::vPackageA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vPackageA)
{
    ui->setupUi(this);

    // Get database connection
    myDB = QSqlDatabase::database();

    defaultPackage(); // call default view set up
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


void vPackageA::defaultPackage()
{
    // Create new database query
    QSqlQuery * qry = new QSqlQuery(myDB);

    // Set up the query to create ordered list of teams, except startTeam
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
            tName = qry->value(0).toString();
            ui->teamList->addItem(tName);
        }
    }
    else
    {
        qDebug() << ("vpackagec Error: qry failed.");
    }
}


void vPackageA::sortTeam()
{
//    qDebug() << "size: " << teamNum;
//    QString temp; // used as temporary storage while swapping
    sortedTeams = new QString[teamNum]; // new object for dynamic
                                        // team array
    sortedDistance = new int[teamNum];  // new object for dynamic
                                        // distance array

    /************************************************************************
     * PROCESS: Copy contents of Selection List (fan's selected teams)
     *          into dynamic array.
     ***********************************************************************/
    // Put startTeam at index 0
    sortedTeams[0] = startTeam;
    sortedDistance[0] = 0;

    // Copy teams from Selection List to dynamic array (sortedTeams)
    for(int i = 1; i < teamNum; i++)
    {
        // Selection List needs i-1 because it starts at 0, but the iteration
        // starts at 1 because [0] is where startTeam was placed.
        sortedTeams[i] = selectionList.at(i-1)->text();
    }
}



void vPackageA::on_confirmButton_clicked()
{

    // Stores selected items from teamList into customList
    ui->sortedTeamList->clear();
    selectionList = ui->teamList->selectedItems();
    teamNum = selectionList.count();
    teamNum++; // Need to add 1 to count the startTeam

    sortTeam();

    // Load all selected, sorted teams into list view
    for(int i = 0; i < teamNum; i++)
    {
        ui->sortedTeamList->addItem(sortedTeams[i]);
    }

    ui->sortedGroup->setEnabled(true);

}
