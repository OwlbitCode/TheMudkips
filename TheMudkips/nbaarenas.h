#ifndef NBAARENAS_H
#define NBAARENAS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>


namespace Ui {
class nbaArenas;
}

class nbaArenas : public QWidget
{
    Q_OBJECT

public:
    explicit nbaArenas(QWidget *parent = nullptr);
    ~nbaArenas();

private slots:
    void on_arenaButton_clicked();

    void on_stadiumCapacityButton_clicked();

    void totalCapacity();

    void on_arenaCB_currentIndexChanged();

private:
    Ui::nbaArenas *ui;
    QSqlDatabase myDB;
    int total;
};

#endif // NBAARENAS_H
