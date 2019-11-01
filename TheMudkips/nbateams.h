#ifndef NBATEAMS_H
#define NBATEAMS_H

#include <QWidget>

namespace Ui {
class nbaTeams;
}

class nbaTeams : public QWidget
{
    Q_OBJECT

public:
    explicit nbaTeams(QWidget *parent = nullptr);
    ~nbaTeams();

private:
    Ui::nbaTeams *ui;
};

#endif // NBATEAMS_H
