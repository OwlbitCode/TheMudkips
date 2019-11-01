#ifndef NBACONFDIV_H
#define NBACONFDIV_H

#include <QWidget>

namespace Ui {
class nbaConfDiv;
}

class nbaConfDiv : public QWidget
{
    Q_OBJECT

public:
    explicit nbaConfDiv(QWidget *parent = nullptr);
    ~nbaConfDiv();

private:
    Ui::nbaConfDiv *ui;
};

#endif // NBACONFDIV_H
