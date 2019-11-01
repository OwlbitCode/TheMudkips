#ifndef VACATION_H
#define VACATION_H

#include <QWidget>

namespace Ui {
class Vacation;
}

class Vacation : public QWidget
{
    Q_OBJECT

public:
    explicit Vacation(QWidget *parent = nullptr);
    ~Vacation();

private:
    Ui::Vacation *ui;
};

#endif // VACATION_H
