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

    // get number of distinct team names in db
    getTeamTotal();

    // create dynamic master list for team names
    teamList = new std::string [teamTotal];

    // populate team master list from db
    getTeamList();

    // create dynamic adjacency matrix (pointers array)
    adj = new float* [teamTotal];

    // create columns for adjacency matrix
    for(int i = 0; i < teamTotal; i++)
    {
        // creates the columns in the 2d dynamic array
        adj[i] = new float[teamTotal];
        // initialize each cell to -1
        memset(adj[i], -1, teamTotal*sizeof(float));
    }

    // populate adjacency matrix (add edges)
    createMatrix();

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
 * getTeamTotal
 * --------------------------------------------------------------------------
 * Gets the total number of distinct beginning team names from distance db.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      myDB is is open and connected
 *
 * POST-CONDITIONS
 *      ==> Nothing.
 ***************************************************************************/
void vPackageC::getTeamTotal()
{
    // Create new database query
    QSqlQuery * qry = new QSqlQuery(myDB);

    // Set up the query to create ordered list of teams, except startTeam
    qry->prepare("SELECT COUNT (DISTINCT `Beg Team`) "
                 "FROM Distances");

    // Execute query if valid
    if(qry->exec())
    {
        qry->next();
        // get total team number
        teamTotal= qry->value(0).toInt();
    }
    else
    {
        qDebug() << ("Package C getTeamTotal Error: qry failed.");
    }
}

/****************************************************************************
 * getTeamList
 * --------------------------------------------------------------------------
 * Create team name master list, sorted in ascending order.  Their index
 * will be used for referencing the team name associated with it.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      myDB is is open and connected
 *
 * POST-CONDITIONS
 *      ==> Nothing.
 ***************************************************************************/
void vPackageC::getTeamList()
{
    int index = 0;

    // Create new database query
    QSqlQuery * qry = new QSqlQuery(myDB);

    // Set up the query to create ordered list of teams, except startTeam
    qry->prepare("SELECT DISTINCT `Beg Team` "
                 "FROM Distances "
                 "ORDER BY `Beg Team` COLLATE NOCASE ASC ");

    // Execute query if valid
    if(qry->exec())
    {
        // Populating master team list from query
        while(qry->next())
        {
            uTeam = qry->value(0).toString();
            teamList[index] = uTeam.toStdString();
            index++;
        }
    }
    else
    {
        qDebug() << ("Package C getTeamList Error: qry failed.");
    }
    qDebug() << "getTeamList Done";
}

/****************************************************************************
 * createMatrix
 * --------------------------------------------------------------------------
 * Creates an adjacency matrix for beginning team name as column (u),
 * ending team name as rows (v), and the distance between them as the weight
 * in the cell.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      myDB is is open and connected
 *
 * POST-CONDITIONS
 *      ==> Nothing.
 ***************************************************************************/
void vPackageC::createMatrix()
{
    int sIndex = 0; // start team index value
    int dIndex = 0; // destination team index value
    bool isFound = false;

    // Create new database query
    QSqlQuery * qry = new QSqlQuery(myDB);

    // Set up the query to create ordered list of teams, except startTeam
    qry->prepare("SELECT * "
                 "FROM Distances");

    // Execute query if valid
    if(qry->exec())
    {
        // Populating list from query
        while(qry->next())
        {
            sIndex = 0; // start team index value
            dIndex = 0; // destination team index value

            // Find start team in team list for its index
            isFound = false;
            uTeam = qry->value(0).toString();
            while(!isFound && sIndex < teamTotal)
            {
                // check if there is a match
                if(teamList[sIndex] == uTeam.toStdString())
                    isFound = true;
                else
                    sIndex++;
            }

            // Find destination team in team list for its index
            isFound = false;
            vTeam = qry->value(2).toString();
            while(!isFound && dIndex < teamTotal)
            {
                // check if there is a match
                if(teamList[dIndex] == vTeam.toStdString())
                    isFound = true;
                else
                    dIndex++;
            }

            distance = qry->value(3).toFloat();

            // Add weighted edge into adjacency matrix
            adj[sIndex][dIndex] = distance;
        }
    }
    else
    {
        qDebug() << ("Package C createMatrix: qry failed.");
    }

    qDebug() << "createMatrix done";
}

/****************************************************************************
 * doDijkstras
 * --------------------------------------------------------------------------
 * Creates a subgraph of shortest distance using dijkstra's algorithm.
 * This is used to determine shortest distance algorithm for this package.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      myDB is is open and connected
 *      adj[][] : adjacency matrix was already created and has data
 *      sTeamIndex: index of starting node.
 *
 * POST-CONDITIONS
 *      ==> Nothing.
 ***************************************************************************/
void vPackageC::doDijkstras()
{
    float lowDist[teamTotal]; // The output array. dist[i] will hold the shortest
                            // distance from src to i

    bool cloudT[teamTotal]; // cloudT[i] will be true if vertex i is included in shortest
                            // path tree or shortest distance from src to i is finalized

    int parentArr[teamTotal]; // Parent array used to store the parent(index u) for child (index v)
    parentArr[0] = 0; // set starting index to 0

    // Initialize all distances as INFINITE and cloudT[] as false
    for (int i = 0; i < teamTotal; i++)
    {
        lowDist[i] = 9999.9f;
        cloudT[i] = false;
    }

    // Distance of source vertex from itself is always 0
    lowDist[sTeamIndex] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < teamTotal - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(lowDist, cloudT);

        // Mark the picked vertex as processed
        cloudT[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < teamTotal; v++)
        {
            // Update dist[v] only if is not in cloudT, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!cloudT[v] && adj[u][v] && (lowDist[u] >= 9999.9f)
                && (lowDist[u] + adj[u][v] < lowDist[v]))
            {
                lowDist[v] = lowDist[u] + adj[u][v];
                parentArr[v] = u;//storing the parent u for child v
            }
        }
    }

    // print the constructed distance array
    displaySolution(lowDist, parentArr);
}

/****************************************************************************
 * minDistance
 * --------------------------------------------------------------------------
 * A utility function to find the vertex with minimum distance value, from
 * the set of vertices not yet included in shortest path tree
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      NONE
 *
 * POST-CONDITIONS
 *      ==> Nothing.
 ***************************************************************************/
int vPackageC::minDistance(float lowDist[], bool cloudT[])
{
    // Initialize min value
    float min = FLT_MAX;
    int minIndex = 0;

    for (int v = 0; v < teamTotal; v++)
        if (cloudT[v] == false && lowDist[v] <= min)
        {
            min = lowDist[v];
            minIndex = v;
        }

    return minIndex;
}

void vPackageC::displaySolution(float lowDist[], int parentArr[])
{
    {
        int p;
        int c;

        for (int i = 0; i < teamTotal; i++)
        {
            p = parentArr[i];
            c=i;

            qDebug() << QString::fromStdString(teamList[i]);

            while(p!=0 && c!=0)
            {
                qDebug() << " <- " << QString::fromStdString(teamList[p]);
                c = p;
                p = parentArr[p];
            }

            if (i!=0)
            {
                qDebug() << " <- " << QString::fromStdString(teamList[p]);
            }
            qDebug() << " | " << lowDist[i] << endl;
        }
    }
}

/****************************************************************************
 * sortTeamNormal
 * --------------------------------------------------------------------------
 * Uses dijkstra's algorithm to create a dynamic array for team order
 * and distance traveled using customList plus startTeam.  This is the
 * NORMAL PACKAGE.  Order is fan choice.
 * --------------------------------------------------------------------------
 * POST-CONDITIONS
 *      ==> Creates sorted dynamic arrays for teams and destinations.
 ***************************************************************************/
// Display dynamic sorted array that will be passed in list
void vPackageC::sortTeamNormal()
{
//    qDebug() << "size: " << teamNum;
//    QString temp; // used as temporary storage while swapping
    sortedTeams = new QString[teamNum]; // new object for dynamic
                                        // team array
    sortedDistance = new float[teamNum];  // new object for dynamic
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
 * sortTeamOptimize
 * --------------------------------------------------------------------------
 * Uses dijkstra's algorithm to create a dynamic array for team order
 * and distance traveled using customList plus startTeam.  This is the
 * OPTIMIZED PACKAGE.  Shortest distance, not fan choice.
 * --------------------------------------------------------------------------
 * POST-CONDITIONS
 *      ==> Creates sorted dynamic arrays for teams and destinations.
 ***************************************************************************/
// Display dynamic sorted array that will be passed in list
void vPackageC::sortTeamOptimize()
{
//    qDebug() << "size: " << teamNum;
//    QString temp; // used as temporary storage while swapping
    sortedTeams = new QString[teamNum]; // new object for dynamic
                                        // team array
    sortedDistance = new float[teamNum];  // new object for dynamic
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

    // Initialize variables for finding the start team index in master list
    bool isFound = false;
    sTeamIndex = 0;
    // find start team index
    while(!isFound)
    {
        if(teamList[sTeamIndex] == startTeam.toStdString())
            isFound = true;
        else
            sTeamIndex++;
    }

    // Used to determine which algorithm to use
    // If checkbox is checked (true)
    if(ui->optimizeBox->isChecked())
    {
        qDebug() << "Optimization: true";
        sortTeamOptimize();
    }
    // If checkbox is unchecked (false)
    else
    {
        qDebug() << "Optimization: false";
        sortTeamNormal();
    }

    // GENERATE DIJKSTRA'S using startTeam and adjacency matrix
//    doDijkstras();

    // Load all selected, sorted teams into list view
    for(int i = 0; i < teamNum; i++)
    {
        ui->sortedTeamList->addItem(sortedTeams[i]);
    }

    ui->sortedGroup->setEnabled(true);
}
