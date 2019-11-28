#ifndef ASOUVENIRS_H
#define ASOUVENIRS_H

#include <QWidget>
#include "QtSql"
#include "databasemanager.h"
#include "QtDebug"

namespace Ui {
class aSouvenirs;
}

class aSouvenirs : public QWidget
{
    Q_OBJECT

public:
    explicit aSouvenirs(QWidget *parent = nullptr);
    ~aSouvenirs();

private slots:
    void on_addSouvenir_clicked();

    void on_editSouvenir_clicked();

    void on_deleteSouvenir_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_editComboBox_activated(const QString &arg1);

    void on_deleteComboBox_activated(const QString &arg1);

private:
    Ui::aSouvenirs *ui;
    QSqlDatabase myDB;
};

#endif // ASOUVENIRS_H
