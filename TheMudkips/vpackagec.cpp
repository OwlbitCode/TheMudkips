#include "vpackagec.h"
#include "ui_vpackagec.h"

/****************************************************************************
 * CONSTRUCTOR
 * --------------------------------------------------------------------------
 * Displays default view for window.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      Database class created to connect to database.
 *
 * POST-CONDITIONS
 *      ==> Displays default view.
 ***************************************************************************/
vPackageC::vPackageC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vPackageC)
{
    ui->setupUi(this);

    // Get database connection
    myDB = QSqlDatabase::database();

    // Display default combobox view which also updates the left list view
    defaultComboBoxView();

    // Set right side to disabled
    ui->sortedGroup->setEnabled(false);
}

/****************************************************************************
 * DESTRUCTOR
 * --------------------------------------------------------------------------
 * DELETES ui
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      ui exists
 *
 * POST-CONDITIONS
 *      ==> Deletes ui
 ***************************************************************************/
vPackageC::~vPackageC()
{
    delete ui;
}

/****************************************************************************
 * defaultListView
 * --------------------------------------------------------------------------
 * Loads all teams from database query into ListWidget, except the startTeam.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      database is open
 *
 * POST-CONDITIONS
 *      ==> Displays teams into List Widget (teamList) on left side.
 ***************************************************************************/
void vPackageC::defaultListView()
{
    // Create new database query
    QSqlQuery * qry = new QSqlQuery(myDB);

//    qDebug() << startTeam;

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
            teamName = qry->value(0).toString();
            ui->teamList->addItem(teamName);
        }
    }
    else
    {
        qDebug() << ("vpackagec Error: qry failed.");
    }
}

/****************************************************************************
 * defaultComboBoxView
 * --------------------------------------------------------------------------
 * Query of all teams is displayed in the combo box.
 * --------------------------------------------------------------------------
 * POST-CONDITIONS
 *      ==> Displays combobox with all team names.
 ***************************************************************************/
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

/****************************************************************************
 * sortTeamList
 * --------------------------------------------------------------------------
 * Uses dijkstra's algorithm to create a dynamic array for team order
 * and distance traveled using customList plus startTeam.
 * --------------------------------------------------------------------------
 * POST-CONDITIONS
 *      ==> Creates sorted dynamic arrays for teams and destinations.
 ***************************************************************************/
// Display dynamic sorted array that will be passed in list
void vPackageC::sortTeamList()
{
//    qDebug() << "size: " << teamNum;
//    QString temp; // used as temporary storage while swapping
    sortedTeams = new QString[teamNum]; // new object for dynamic
                                        // team array
    sortedDistance = new int[teamNum];  // new object for dynamic
                                        // distance array

    /************************************************************************
     * PROCESS: Copy contents of customList (fan's selected teams)
     *          into dynamic array.
     ***********************************************************************/
    // Put startTeam at index 0
    sortedTeams[0] = startTeam;
    sortedDistance[0] = 0;

    // Copy teams from customList to dynamic array (sortedTeams)
    for(int i = 1; i < teamNum; i++)
    {
        // customList needs i-1 because it starts at 0, but the iteration
        // starts at 1 because [0] is where startTeam was placed.
        sortedTeams[i] = customList.at(i-1)->text();
    }
}

/****************************************************************************
 * on_cancelButton_clicked
 * --------------------------------------------------------------------------
 * Closes this window.
 * --------------------------------------------------------------------------
 * POST-CONDITIONS
 *      ==> Closes this window.
 ***************************************************************************/
void vPackageC::on_cancelButton_clicked()
{
    this->close();
}

/****************************************************************************
 * on_startButton_clicked
 * --------------------------------------------------------------------------
 * Closes this window and opens the simulation window.
 * --------------------------------------------------------------------------
 * POST-CONDITIONS
 *      ==> Closes this window and opens simulation window.
 ***************************************************************************/
void vPackageC::on_startButton_clicked()
{
    simulationWindow = new vSimulation;
    simulationWindow->show();

    this->close();
}

/****************************************************************************
 * on_startTeam_currentIndexChanged
 * --------------------------------------------------------------------------
 * Updates startTeam to the selected item in the combobox and update
 * teamList with all team names, excluding the startTeam.
 * --------------------------------------------------------------------------
 * POST-CONDITIONS
 *      ==> Updates teamList view.
 ***************************************************************************/
void vPackageC::on_startTeam_currentIndexChanged(const QString &arg1)
{
    startTeam = arg1;
//    qDebug() << startTeam;
    ui->teamList->clear();
    defaultListView();
}

/****************************************************************************
 * on_confirmButton_clicked
 * --------------------------------------------------------------------------
 * Stores selected teams into an array list.  Get teamNum and set
 * startTeam.  Use sorting algorithm in sortTeamList to get dynamic
 * arrays.  And display the results in the dynamic arrays.
 * --------------------------------------------------------------------------
 * POST-CONDITIONS
 *      ==> Displays resulting dynamic arrays on right side of window.
 ***************************************************************************/
void vPackageC::on_confirmButton_clicked()
{
    // Stores selected items from teamList into customList
    ui->sortedTeamList->clear();
    customList = ui->teamList->selectedItems();
    teamNum = customList.count();
    teamNum++; // Need to add 1 to count the startTeam
    startTeam = ui->startTeam->currentText();

    sortTeamList();

    // Load all selected, sorted teams into list view
    for(int i = 0; i < teamNum; i++)
    {
        ui->sortedTeamList->addItem(sortedTeams[i]);
    }

    ui->sortedGroup->setEnabled(true);
}
