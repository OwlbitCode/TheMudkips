#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

#include "ateam.h"
#include "aarena.h"
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

    void on_page3Button_clicked();

private:
    Ui::Admin *ui;

    aTeam teamWindow;
    aArena arenaWindow;
    aSouvenirs souvenirsWindow;
};

#endif // ADMIN_H
