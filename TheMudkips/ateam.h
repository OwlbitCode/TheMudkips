#ifndef ATEAM_H
#define ATEAM_H

#include<QtSql>
#include <QWidget>
#include"databasemanager.h"
#include"addteam.h"
#include<QtSql>
#include<iostream>
namespace Ui {
class aTeam;
}

class aTeam : public QWidget
{
    Q_OBJECT

public:
    explicit aTeam(QWidget *parent = nullptr);
    ~aTeam();

private slots:

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::aTeam *ui;
    QSqlDatabase myDb;
    addTeam window;
};

#endif // ATEAM_H
