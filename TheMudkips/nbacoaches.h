#ifndef NBACOACHES_H
#define NBACOACHES_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class nbaCoaches;
}

class nbaCoaches : public QWidget
{
    Q_OBJECT

public:
    explicit nbaCoaches(QWidget *parent = nullptr);
    ~nbaCoaches();

private slots:
    void on_viewAllButton_clicked();

    void on_coachCB_currentIndexChanged();

private:
    Ui::nbaCoaches *ui;
    QSqlDatabase myDB;
};

#endif // NBACOACHES_H
