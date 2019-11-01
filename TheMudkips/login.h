#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "databasemanager.h"
#include "admin.h"
#include "vacation.h"
#include "nbainfo.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void connectToDB();

private slots:
    void on_nbaInfoButton_clicked();

    void on_loginButton_clicked();

    void on_exitProgramButton_clicked();

    void on_usernameLineEdit_returnPressed();

    void on_passwordLineEdit_returnPressed();

private:
    Ui::Login *ui;
    databaseManager myDB;
    Vacation *vacationWindow;
    Admin   *adminWindow;
    NBAInfo *nbaWindow;
};

#endif // LOGIN_H
