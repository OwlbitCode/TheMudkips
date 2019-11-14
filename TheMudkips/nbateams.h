#ifndef NBATEAMS_H
#define NBATEAMS_H

#include <QWidget>
#include "QtSql"
#include "databasemanager.h"
#include "QtDebug"

namespace Ui {
class nbaTeams;
}

class nbaTeams : public QWidget
{
    Q_OBJECT

public:
    explicit nbaTeams(QWidget *parent = nullptr);

    ~nbaTeams();

private slots:

    void on_EasternComboBox_activated(const QString &arg1);

    void on_westernComboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::nbaTeams *ui;
    QSqlDatabase myDB;
};

#endif // NBATEAMS_H
