#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

/****************************************************************************
 * METHOD - connectToDB
 * --------------------------------------------------------------------------
 * This method creates and opens a database connection and displays a
 * qDebug message that the database access is open.  This method is used
 * with a valid login (traveler or admin).  If database is already
 * connected and open, then only the qDebug message is displayed.
 * NOTE: Use with valid login username/password only (traveler or admin)
 * --------------------------------------------------------------------------
 * PRE-CONDITIONS
 *      No parameters are required.
 *
 * POST-CONDITIONS
 *      ==> Returns nothing.
 *      ==> Creates and connects to SQLite database if not open
 ***************************************************************************/
void Login::connectToDB()
{
    bool isOpen = false; // CALC - Set database open status to false

    // Create and open a database connection
    // Return if database opened successfully or not
    isOpen = myDB.openDB();

    // Display message if database connection was successful
    if(isOpen)
    {
        qDebug() << "Success: Able to access open database";
    }
}

void Login::on_nbaInfoButton_clicked()
{
    connectToDB();
    nbaWindow = new NBAInfo();
    nbaWindow->show();
}

void Login::on_loginButton_clicked()
{
    QString username;   //IN, CALC - username
    QString password;   //IN, CALC - password

    username = ui->usernameLineEdit->text();
    password = ui->passwordLineEdit->text();

    // Swap below if statements when changing functionality
    //if(username == "fan" && password == "123")
    if(username == "fan")
    {
        ui->passwordLineEdit->setText("");
        ui->usernameLineEdit->setText("");

        ui->errorLabel->setText("");

        connectToDB();
        vacationWindow = new Vacation();
        vacationWindow->show();
    }
    // Swap below if statements when changing functionality
    //else if(username == "admin" && password == "456")
    else if(username == "admin")
    {
        ui->passwordLineEdit->setText("");
        ui->usernameLineEdit->setText("");

        ui->errorLabel->setText("");

        connectToDB();
        adminWindow = new Admin();
        adminWindow->show();
    }
    else
    {

        ui->errorLabel->setText("** Invalid Username or Password");
        ui->passwordLineEdit->setText("");
        ui->usernameLineEdit->setText("");
    }
}

void Login::on_exitProgramButton_clicked()
{
    myDB.closeDB();
    this->close();
}

void Login::on_usernameLineEdit_returnPressed()
{
    on_loginButton_clicked();
}

void Login::on_passwordLineEdit_returnPressed()
{
    on_loginButton_clicked();
}


