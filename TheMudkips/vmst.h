#ifndef VMST_H
#define VMST_H

#include <QWidget>

namespace Ui {
class vMST;
}

class vMST : public QWidget
{
    Q_OBJECT

public:
    explicit vMST(QWidget *parent = nullptr);
    ~vMST();

private:
    Ui::vMST *ui;
};

#endif // VMST_H
