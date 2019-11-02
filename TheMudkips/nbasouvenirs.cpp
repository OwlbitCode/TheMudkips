#include "nbasouvenirs.h"
#include "ui_nbasouvenirs.h"

/****************************************************************************
 * CONSTRUCTOR
 * --------------------------------------------------------------------------
 * Displays default view for window.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      Database class created to connect to database.
 *
 * POST-CONDITIONS
 *      ==> Displays window in default view.
 ***************************************************************************/
nbaSouvenirs::nbaSouvenirs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nbaSouvenirs)
{
    ui->setupUi(this);

    // Get database connection
    myDB = QSqlDatabase::database();

    QString teamName; // Place holder for setting up List

    // Create new database query
    QSqlQuery * qry = new QSqlQuery(myDB);

    // Set up the query to create ordered list of destination cities
    qry->prepare("SELECT DISTINCT `Team Name` "
                 "FROM Souvenirs "
                 "ORDER BY `Team Name` COLLATE NOCASE ASC ");

    // Execute query if valid
    if(qry->exec())
    {
        // Populating list from query
        while(qry->next())
        {
            teamName = qry->value(0).toString();
            ui->teamTable->addItem(teamName);
        }
    }
    else
    {
        qDebug() << ("nbaSouvenir Error: qry failed in defaultview().");
    }

    // Default select index 0 to display
    on_teamTable_currentTextChanged(ui->teamTable->item(0)->text());
    ui->teamTable->setCurrentRow(0);
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
nbaSouvenirs::~nbaSouvenirs()
{
    delete ui;
}

/****************************************************************************
 * METHOD - on_teamTable_currentTextChanged
 * --------------------------------------------------------------------------
 * This method updates team name label and souvenir prices for the selected
 * team.
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      currentText : selected team name from teamTable
 *
 * POST-CONDITIONS
 *      ==> Returns nothing.
 ***************************************************************************/
void nbaSouvenirs::on_teamTable_currentTextChanged(const QString &currentText)
{
    QString teamName = currentText;

    // Display current team selected in line
    ui->teamLine->setText(teamName);

    // Create new database query
    QSqlQuery * qry = new QSqlQuery(myDB);

    // Set up the query to create ordered list of NBA teams
    qry->prepare("SELECT * "
                 "FROM Souvenirs "
                 "ORDER BY `Team Name` COLLATE NOCASE ASC ");

    // Execute query if valid
    if(qry->exec())
    {
        // Populating line text
        while(qry->next())
        {
            teamName = qry->value(0).toString();
            ui->bbLine->setText(QString::number(qry->value(1).toFloat(), 'f', 2));
            ui->penLine->setText(QString::number(qry->value(2).toFloat(), 'f', 2));
            ui->picLine->setText(QString::number(qry->value(3).toFloat(), 'f', 2));
            ui->jerseyLine->setText(QString::number(qry->value(4).toFloat(), 'f', 2));
        }
    }
    else
    {
        qDebug() << ("nbaSouvenir Error: qry failed in defaultview().");
    }
}
