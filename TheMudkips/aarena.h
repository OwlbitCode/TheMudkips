#ifndef AARENA_H
#define AARENA_H

#include <QWidget>
#include<iostream>
#include"databasemanager.h"
#include<QtSql>
namespace Ui {
class aArena;
}

class aArena : public QWidget
{
    Q_OBJECT

public:
    explicit aArena(QWidget *parent = nullptr);
    ~aArena();

private slots:


    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::aArena *ui;
    QSqlDatabase myDb;
};

#endif // AARENA_H
