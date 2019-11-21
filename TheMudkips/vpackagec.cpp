#include "vpackagec.h"
#include "ui_vpackagec.h"

vPackageC::vPackageC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vPackageC)
{
    ui->setupUi(this);

    // Get database connection
    myDB = QSqlDatabase::database();

    defaultComboBoxView();

    ui->sortedGroup->setEnabled(false);
}

vPackageC::~vPackageC()
{
    delete ui;
}

void vPackageC::defaultListView()
{
    // Create new database query
    QSqlQuery * qry = new QSqlQuery(myDB);

    qDebug() << startTeam;

    // Set up the query to create ordered list of destination teams
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
            teamName = qry->value(0).toString();
            ui->teamList->addItem(teamName);
        }
    }
    else
    {
        qDebug() << ("vpackagec Error: qry failed.");
    }
}

void vPackageC::defaultComboBoxView()
{
    QSqlQuery * qry1 = new QSqlQuery(myDB);
    QSqlQueryModel * combo = new QSqlQueryModel();
    qry1->prepare("SELECT DISTINCT `Beg Team` "
                  "FROM Distances "
                  "ORDER BY `Beg Team` ASC ");
    qry1->exec();

    combo->setQuery(*qry1);

    ui->startTeam->setModel(combo);
    teamName = ui->startTeam->currentText();
}

// Display dynamic sorted array that will be passed in list
void vPackageC::sortTeamList()
{
    qDebug() << "size: " << teamNum;
    QString temp; // used as temporary storage while swapping
    sortedTeams = new QString[teamNum]; // new object for dynamic
                                        // team array
    sortedDistance = new int[teamNum];  // new object for dynamic
                                        // distance array

    /************************************************************************
     * PROCESS: Copy contents of customList (fan's selected teams)
     *          into dynamic array.
     ***********************************************************************/
    sortedTeams[0] = startTeam;
    sortedDistance[0] = 0;

    for(int i = 1; i < teamNum; i++)
    {
        sortedTeams[i] = customList.at(i-1)->text();
    }
}

void vPackageC::on_cancelButton_clicked()
{
    this->close();
}

void vPackageC::on_startButton_clicked()
{
    simulationWindow = new vSimulation;
    simulationWindow->show();

    this->close();
}

void vPackageC::on_startTeam_currentIndexChanged(const QString &arg1)
{
    startTeam = arg1;
    qDebug() << startTeam;
    ui->teamList->clear();
    defaultListView();
}

void vPackageC::on_confirmButton_clicked()
{
    // Stores selected items from teamList into customList
    ui->sortedTeamList->clear();
    customList = ui->teamList->selectedItems();
    teamNum = customList.count();
    teamNum++;
    startTeam = ui->startTeam->currentText();

    sortTeamList();

    // Load all selected, sorted teams into list view
    for(int i = 0; i < teamNum; i++)
    {
        ui->sortedTeamList->addItem(sortedTeams[i]);
    }

    ui->sortedGroup->setEnabled(true);
}
