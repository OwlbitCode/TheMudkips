#include "vbfs.h"
#include "ui_vbfs.h"

vBFS::vBFS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vBFS)
{
    ui->setupUi(this);

    // get number of distinct team names in db
    getNumTeams();

    // create dynamic master list for team names
    teamList = new std::string [numTeams];

    // populate team master list from db
    getTeamList();

    // get root team index
    rootIndex = 0;
    bool isFound = false;
    while(!isFound)
    {
        if(teamList[rootIndex] == "Los Angeles Lakers")
            isFound = true;
        else
            rootIndex++;
    }
//    qDebug() << rootIndex;

    // create dynamic adjacency matrix (pointers array)
    adj = new float* [numTeams];

    // create columns for adjacency matrix
    for(int i = 0; i < numTeams; i++)
    {
        adj[i] = new float[numTeams];
        // initialize each cell to -1
        memset(adj[i], -1, numTeams*sizeof(float));
    }

    // populate adjacency matrix (add edges)
    createMatrix();

    BFS();

    ui->distanceLine->setText(QString::number(tDistance,'f', 2));
}

vBFS::~vBFS()
{
    delete [] teamList;
    delete ui;
}

// Gets number of distinct beginning team names from distance database
void vBFS::getNumTeams()
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
        numTeams = qry->value(0).toInt();
    }
    else
    {
        qDebug() << ("bfs Error: qry failed.");
    }
//    qDebug() << numTeams;
}

// Create team name list, sorted in ascending
// Used for indexing team names
void vBFS::getTeamList()
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
        // Populating list from query
        while(qry->next())
        {
            uTeam = qry->value(0).toString();
            teamList[index] = uTeam.toStdString();
            index++;
        }
    }
    else
    {
        qDebug() << ("bfs getTeamList Error: qry failed.");
    }
}

void vBFS::createMatrix()
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
            while(!isFound && sIndex < numTeams)
            {
                if(teamList[sIndex] == uTeam.toStdString())
                    isFound = true;
                else
                    sIndex++;
            }
//            qDebug() << sIndex;

            // Find destination team in team list for its index
            isFound = false;
            vTeam = qry->value(2).toString();
            while(!isFound && dIndex < numTeams)
            {
                if(teamList[dIndex] == vTeam.toStdString())
                    isFound = true;
                else
                    dIndex++;
            }
//            qDebug() << dIndex;

            distance = qry->value(3).toFloat();
//            qDebug() << distance;

            // Add edge
            adj[sIndex][dIndex] = distance;
        }
    }
    else
    {
        qDebug() << ("vpackagec Error: qry failed.");
    }
}

void vBFS::BFS()
{
    std::vector<bool> visited(numTeams,false);
    std::vector<int> q;
    std::vector<std::tuple<int, int, float>> temp;
    int u, v, wt, vis;
    QString tempStr;

    q.push_back(rootIndex);
    visited[rootIndex] = true;
    tempStr = QString::fromStdString(teamList[rootIndex]);
    ui->bfsList->addItem(tempStr);

    while(!q.empty())
    {
        // get all destinations from origin
        while(!q.empty())
        {
            vis = q[0];
            q.erase(q.begin());
            for(int i = 0; i < numTeams; i++)
            {
                if(adj[vis][i] >= 0 && (!visited[i]))
                    temp.push_back(std::make_tuple(vis,i,adj[vis][i]));
            }
            sort(temp.begin(), temp.end(),
                 [](std::tuple<int, int, float> const &a, std::tuple<int, int, float> &b)
                {
                     return (std::get<2>(a) < std::get<2>(b));
                });
        }

        ui->bfsList->addItem("--------- Level Change ---------");

        for(auto it = temp.begin(); it != temp.end(); ++it)
        {
            u = std::get<0>(*it);
            v = std::get<1>(*it);
            wt = std::get<2>(*it);

//            qDebug() << u << " " << v << wt;

            if(!visited[v])
            {
                tDistance = tDistance + wt;
                q.push_back(v);
                visited[v] = true;
                tempStr = QString::fromStdString(teamList[v]);
                ui->bfsList->addItem(tempStr);
            }
        }

        temp.clear();
    }
}

bool vBFS::sortedbyWeight(const std::tuple<int, int, float>& a, const std::tuple<int, int, float>& b)
{
    return (std::get<2>(a) < std::get<2>(b));
}
