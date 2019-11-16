#ifndef NBACONFDIV_H
#define NBACONFDIV_H

#include <QWidget>
#include "QtSql"
#include "databasemanager.h"
#include "QtDebug"

namespace Ui {
class nbaConfDiv;
}

class nbaConfDiv : public QWidget
{
    Q_OBJECT

public:
    explicit nbaConfDiv(QWidget *parent = nullptr);
    ~nbaConfDiv();

private slots:
    void on_TeamComboBox_activated(const QString &arg1);

    void on_teamComboBox_activated(const QString &arg1);

    void on_sortNameButton_clicked();

    void on_sortYearButton_clicked();

private:
    Ui::nbaConfDiv *ui;
    QSqlDatabase myDB;
};

#endif // NBACONFDIV_H
