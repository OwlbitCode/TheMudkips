#ifndef VSIMULATION_H
#define VSIMULATION_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class vSimulation;
}

class vSimulation : public QWidget
{
    Q_OBJECT

public:
    explicit vSimulation(QWidget *parent = nullptr);
    ~vSimulation();

private slots:
    void on_cancelButton_clicked();

    void on_endButton_clicked();

private:
    Ui::vSimulation *ui;
    QSqlDatabase myDB;
};

#endif // VSIMULATION_H
