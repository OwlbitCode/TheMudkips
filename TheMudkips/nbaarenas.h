#ifndef NBAARENAS_H
#define NBAARENAS_H

#include <QWidget>

namespace Ui {
class nbaArenas;
}

class nbaArenas : public QWidget
{
    Q_OBJECT

public:
    explicit nbaArenas(QWidget *parent = nullptr);
    ~nbaArenas();

private:
    Ui::nbaArenas *ui;
};

#endif // NBAARENAS_H
