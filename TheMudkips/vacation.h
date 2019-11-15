#ifndef VACATION_H
#define VACATION_H

#include <QWidget>
#include <vpackagea.h>
#include <vpackageb.h>
#include <vpackagec.h>
#include <vsimulation.h>
#include <vbfs.h>
#include <vdfs.h>
#include <vmst.h>

namespace Ui {
class Vacation;
}

class Vacation : public QWidget
{
    Q_OBJECT

public:
    explicit Vacation(QWidget *parent = nullptr);
    ~Vacation();

private slots:
    void on_packagesButton_clicked();

    void on_bfsButton_clicked();

    void on_dfsButton_clicked();

    void on_mstButton_clicked();

    void on_exitButton_clicked();

    void on_packageAButton_clicked();

    void on_packageBButton_clicked();

    void on_packageCButton_clicked();

private:
    Ui::Vacation *ui;

    vPackageA *packageAWindow;
    vPackageB *packageBWindow;
    vPackageC *packageCWindow;
    vBFS      bfsWindow;
    vDFS      dfsWindow;
    vMST      mstWindow;
};

#endif // VACATION_H
