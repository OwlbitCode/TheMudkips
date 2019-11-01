#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

#include "ateam.h"
#include "asouvenirs.h"

namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_homeButton_clicked();

    void on_page1Button_clicked();

    void on_page2Button_clicked();

    void on_exitButton_clicked();

private:
    Ui::Admin *ui;

    aTeam teamWindow;
    aSouvenirs souvenirsWindow;
};

#endif // ADMIN_H
