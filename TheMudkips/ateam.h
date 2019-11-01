#ifndef ATEAM_H
#define ATEAM_H

#include <QWidget>

namespace Ui {
class aTeam;
}

class aTeam : public QWidget
{
    Q_OBJECT

public:
    explicit aTeam(QWidget *parent = nullptr);
    ~aTeam();

private:
    Ui::aTeam *ui;
};

#endif // ATEAM_H
