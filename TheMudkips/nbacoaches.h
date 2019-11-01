#ifndef NBACOACHES_H
#define NBACOACHES_H

#include <QWidget>

namespace Ui {
class nbaCoaches;
}

class nbaCoaches : public QWidget
{
    Q_OBJECT

public:
    explicit nbaCoaches(QWidget *parent = nullptr);
    ~nbaCoaches();

private:
    Ui::nbaCoaches *ui;
};

#endif // NBACOACHES_H
